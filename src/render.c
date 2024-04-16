/*
 * @author Ethan Uppal
 * @copyright Copyright (C) 2024 Ethan Uppal. All rights reserved.
 */

#include "render.h"
#include "intersect.h"

void render(const struct frame* frame, const struct mesh* scene[],
    size_t mesh_count, struct camera camera) {
    double x_scale = camera.vb_width / (double)frame->width;
    double y_scale = camera.vb_height / (double)frame->height;

    struct vector dir = camera.focus;
    v_normalize(&dir);

    struct vector w_hat = v_cross(camera.h_hat, dir);
    v_normalize(&w_hat);  // no-op

    for (size_t j = 0; j < frame->height; j++) {
        for (size_t i = 0; i < frame->width; i++) {
            struct vector src = v_add(v_scale(w_hat, (double)i * x_scale
                                                         - camera.vb_width / 2),
                v_scale(camera.h_hat,
                    camera.vb_height / 2 - (double)j * y_scale));
            src = v_add(src, camera.pos);

            // you'd update dir if this was perspective.

            frame->buffer[j * frame->width + i] = 0x0;

            for (size_t k = 0; k < mesh_count; k++) {
                const struct mesh* mesh = scene[k];
                if (intersect_aabb(src, dir, mesh_get_aabb(mesh))) {
                    for (size_t l = 0; l < mesh_n_faces(mesh); l++) {
                        scalar_t dist;
                        struct vector pos;
                        if (intersect_face(src, dir, mesh, l, &dist, &pos)) {
                            frame->buffer[j * frame->width + i] = 0x00FFFFFF;
                            break;
                        }
                    }
                    break;
                }
            }
        }
    }
}
