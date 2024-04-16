/*
 * @author Ethan Uppal
 * @copyright Copyright (C) 2024 Ethan Uppal. All rights reserved.
 */

#pragma once

#include <stdbool.h>
#include "mesh.h"

/** Returns `true` if and only if the ray starting at `src` in direction `dir`
 * intersects the bounding box `aabb`.
 *
 * @pre `dir` is normalized.
 */
bool intersect_aabb(struct vector src, struct vector dir,
    const struct aabb* aabb);

/** Returns `true` if and only if the ray starting at `src` in direction `dir`
 * intersects the face in `mesh` at index `face_i`. If `true`, `pos` is
 * initialized to the location of the intersection.
 *
 * @pre `dir` is normalized.
 */
bool intersect_face(struct vector src, struct vector dir,
    const struct mesh* mesh, size_t face_i, scalar_t* dist, struct vector* pos);
