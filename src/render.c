/*
 * @author Ethan Uppal
 * @copyright Copyright (C) 2024 Ethan Uppal. All rights reserved.
 */

#include <math.h>
#include "render.h"
#include "intersect.h"

bool raycast(const struct mesh* scene[], size_t mesh_count, struct vector src,
    struct vector dir, struct ray_intersection* intersect) {
    // globally closest intersection (if one exists)
    scalar_t closest_dist = INFINITY;
    struct vector closest_pos;
    const struct mesh* closest_mesh;
    size_t closest_face_i = 0;

    for (size_t k = 0; k < mesh_count; k++) {
        const struct mesh* mesh = scene[k];
        if (intersect_aabb(src, dir, mesh_get_aabb(mesh))) {
            for (size_t i = 0; i < mesh_n_faces(mesh); i++) {
                scalar_t dist;
                struct vector pos;
                if (intersect_face(src, dir, mesh, i, &dist, &pos)) {
                    if (dist < closest_dist) {
                        closest_dist = dist;
                        closest_pos = pos;
                        closest_mesh = mesh;
                        closest_face_i = i;
                    }
                }
            }
        }
    }

    intersect->dist = closest_dist;
    intersect->pos = closest_pos;
    intersect->mesh = closest_mesh;
    intersect->face_i = closest_face_i;

    return closest_dist < INFINITY;
}

void render(const struct frame* frame, const struct scene* scene,
    const struct camera* camera) {
    double x_scale = camera->vb_width / (double)frame->width;
    double y_scale = camera->vb_height / (double)frame->height;

    struct vector dir = camera->focus;
    v_normalize(&dir);  // no-op

    // gram schmidt to always point higher in y
    // TODO: is allow for user defined up vector
    struct vector h_hat = camera->focus;
    h_hat.y += 1;
    h_hat = v_sub(h_hat, v_scale(dir, v_dot(h_hat, dir) / v_dot(dir, dir)));
    v_normalize(&h_hat);

    struct vector w_hat = v_cross(h_hat, dir);
    v_normalize(&w_hat);  // no-op

    for (size_t j = 0; j < frame->height; j++) {
        for (size_t i = 0; i < frame->width; i++) {
            struct vector src = v_add(
                v_scale(w_hat, (double)i * x_scale - camera->vb_width / 2),
                v_scale(h_hat, camera->vb_height / 2 - (double)j * y_scale));
            src = v_add(src, camera->pos);

            // you'd update dir if this was perspective and also edit it above.

            frame->buffer[j * frame->width + i] = 0x0;

            struct ray_intersection intersect;
            if (raycast(scene->meshes, scene->mesh_count, src, dir,
                    &intersect)) {
                // https://ocw.mit.edu/courses/6-837-computer-graphics-fall-2012/b86de2fe1a1084e56148f293da4a4dfd_MIT6_837F12_Lec15.pdf
                frame->buffer[j * frame->width + i] =
                    mesh_get_face(intersect.mesh, intersect.face_i).color;
            }
        }
    }
}
