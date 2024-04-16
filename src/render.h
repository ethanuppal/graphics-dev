/*
 * @author Ethan Uppal
 * @copyright Copyright (C) 2024 Ethan Uppal. All rights reserved.
 */

#pragma once

#include <stddef.h>
#include "window.h"
#include "mesh.h"

struct view_box {
    double min_x;
    double min_y;
    double max_x;
    double max_y;
    double z_focus;
};

/** Renders the `mesh_count` objects in `scene` to `frame`, viewing through
 * `vb`. */
void render(const struct frame* frame, const struct mesh* scene[],
    size_t mesh_count, struct view_box vb);
