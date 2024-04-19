/*
 * @author Ethan Uppal
 * @copyright Copyright (C) 2024 Ethan Uppal. All rights reserved.
 */

#pragma once

#include <stdio.h>
#include <stdint.h>
#include "vector.h"

/** The indices of the vertices in a mesh that form a triangular face. */
struct face {
    size_t v1;
    size_t v2;
    size_t v3;
    uint32_t color;  ///< temp
};

/** A bounding box. */
struct aabb {
    struct vector min;
    struct vector max;
};

/** A polygon built from triangle primitives. */
struct mesh;

/** Loads a mesh from a file. You must call `mesh_destroy` to release it
 * afterward.
 *
 * @returns `NULL` on failure. */
struct mesh* mesh_load(FILE* file);

/** Directly after calling `mesh_load`, this function will return a string if
 * there was an error, and `"No error"` otherwise. */
const char* mesh_load_error(void);

/** @see mesh_load */
void mesh_destroy(struct mesh* mesh);

/** The number of vertices in `mesh`. */
size_t mesh_n_vertices(const struct mesh* mesh);

/** The number of faces in `mesh`. */
size_t mesh_n_faces(const struct mesh* mesh);

/** The `i`th vertex in `mesh`. */
struct vector mesh_get_vertex(const struct mesh* mesh, size_t i);

/** The `i`th face in `mesh`. */
struct face mesh_get_face(const struct mesh* mesh, size_t i);

/** The bounding box around `mesh`. */
const struct aabb* mesh_get_aabb(const struct mesh* mesh);
