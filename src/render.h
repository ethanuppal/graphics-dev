/*
 * @author Ethan Uppal
 * @copyright Copyright (C) 2024 Ethan Uppal. All rights reserved.
 */

#pragma once

#include <stddef.h>
#include "window.h"
#include "mesh.h"
#include "light.h"

struct camera {
    struct vector pos;    ///< The location of the camera.
    struct vector focus;  ///< The direction of the camera and the distance of
                          ///< the view box from the camera.
    double vb_width;      ///< The width of the view box.
    double vb_height;     ///< The height of the view box.
};

struct ray_intersection {
    double dist;
    struct vector pos;
    const struct mesh* mesh;
    size_t face_i;
};

struct scene {
    const struct mesh** meshes;
    size_t mesh_count;
    const struct light* lights;
    size_t light_count;
};

/** Returns `true` if there is a ray intersection and initializes `intersect`
 * with the information of the closest intersection. Otherwise, simply returns
 * `false`. */
bool raycast(const struct mesh* scene[], size_t mesh_count, struct vector src,
    struct vector dir, struct ray_intersection* intersect);

/** Renders `scene` to `frame` as viewed through `camera`. */
void render(const struct frame* frame, const struct scene* scene,
    const struct camera* camera);
