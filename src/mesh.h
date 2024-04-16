/*
 * @author Ethan Uppal
 * @copyright Copyright (C) 2024 Ethan Uppal. All rights reserved.
 */

#pragma once

#include <stdio.h>

struct vector {
    double x;
    double y;
    double z;
};

struct face {
    size_t v1;
    size_t v2;
    size_t v3;
};

struct aabb {
    struct vector min;
    struct vector max;
};

struct mesh;

struct mesh* mesh_load(FILE* file);

void mesh_destroy(struct mesh* mesh);

size_t mesh_n_vertices(const struct mesh* mesh);
size_t mesh_n_faces(const struct mesh* mesh);
struct vector mesh_get_vertex(const struct mesh* mesh, size_t i);
struct face mesh_get_face(const struct mesh* mesh, size_t i);
const struct aabb* mesh_get_aabb(const struct mesh* mesh);
