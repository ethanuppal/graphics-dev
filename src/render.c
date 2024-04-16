/*
 * @author Ethan Uppal
 * @copyright Copyright (C) 2024 Ethan Uppal. All rights reserved.
 */

#include "render.h"
#include "intersect.h"

void render(const struct frame* frame, const struct mesh* scene[],
    size_t mesh_count, struct view_box vb) {
    double vb_width = vb.max_x - vb.min_x;
    double vb_height = vb.max_y - vb.min_y;
    double x_scale = vb_width / (double)frame->width;
    double y_scale = vb_height / (double)frame->height;

    for (size_t j = 0; j < frame->height; j++) {
        for (size_t i = 0; i < frame->width; i++) {
            struct vector src;
            src.x = (double)i * x_scale + vb.min_x;
            src.y = vb.max_y - (double)j * y_scale;
            src.z = vb.z_focus;

            struct vector dir;
            dir.x = 0;
            dir.y = 0;
            dir.z = 1;

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
