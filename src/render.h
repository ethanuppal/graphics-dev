/*
 * @author Ethan Uppal
 * @copyright Copyright (C) 2024 Ethan Uppal. All rights reserved.
 */

#pragma once

#include <stddef.h>
#include "window.h"
#include "mesh.h"

struct camera {
    struct vector pos;    ///< The location of the camera.
    struct vector focus;  ///< The direction of the camera and the distance of
                          ///< the view box from the camera.
    struct vector h_hat;  ///< A unit vector in the upward direction on the view
                          ///< box. `h_hat` must be orthogonal to `focus`.
    double vb_width;      ///< The width of the view box.
    double vb_height;     ///< The height of the view box.
};

/** Renders the `mesh_count` objects in `scene` to `frame`, viewing through
 * `camera`. */
void render(const struct frame* frame, const struct mesh* scene[],
    size_t mesh_count, struct camera camera);
