/*
 * @author Ethan Uppal
 * @copyright Copyright (C) 2024 Ethan Uppal. All rights reserved.
 */

#include "mesh.h"
#include <stdlib.h>
#include <math.h>

struct mesh {
    size_t n_vertices;
    size_t n_faces;
    struct vector* vertices;
    struct face* faces;
    struct aabb aabb;
};

struct mesh* mesh_load(FILE* file) {
    size_t n_vertices;
    size_t n_faces;
    if (fscanf(file, "%zu %zu\n", &n_vertices, &n_faces) < 2) {
        exit(1);
    }
    struct mesh* mesh = malloc(sizeof(*mesh));
    if (!mesh) {
        exit(1);
    }

    mesh->n_vertices = n_vertices;
    mesh->n_faces = n_faces;
    mesh->aabb.min.x = INFINITY;
    mesh->aabb.min.y = INFINITY;
    mesh->aabb.min.z = INFINITY;
    mesh->aabb.max.x = -INFINITY;
    mesh->aabb.max.y = -INFINITY;
    mesh->aabb.max.z = -INFINITY;

    mesh->vertices = malloc(sizeof(*mesh->vertices) * n_vertices);
    if (!mesh->vertices) {
        exit(1);
    }

    mesh->faces = malloc(sizeof(*mesh->faces) * n_faces);
    if (!mesh->faces) {
        exit(1);
    }

    for (size_t i = 0; i < n_vertices; i++) {
        struct vector vertex;
        if (fscanf(file, "%lf %lf %lf\n", &vertex.x, &vertex.y, &vertex.z)
            < 3) {
            exit(1);
        }
        mesh->vertices[i] = vertex;

        if (vertex.x < mesh->aabb.min.x) {
            mesh->aabb.min.x = vertex.x;
        } else if (vertex.x > mesh->aabb.max.x) {
            mesh->aabb.max.x = vertex.x;
        }
        if (vertex.y < mesh->aabb.min.y) {
            mesh->aabb.min.y = vertex.y;
        } else if (vertex.y > mesh->aabb.max.y) {
            mesh->aabb.max.y = vertex.y;
        }
        if (vertex.z < mesh->aabb.min.z) {
            mesh->aabb.min.z = vertex.z;
        } else if (vertex.z > mesh->aabb.max.z) {
            mesh->aabb.max.z = vertex.z;
        }
    }

    for (size_t i = 0; i < n_faces; i++) {
        struct face face;
        if (fscanf(file, "%zu %zu %zu\n", &face.v1, &face.v2, &face.v3) < 3) {
            exit(1);
        }
        mesh->faces[i] = face;
    }

    return mesh;
}

void mesh_destroy(struct mesh* mesh) {
    free(mesh->vertices);
    free(mesh->faces);
    free(mesh);
}

size_t mesh_n_vertices(const struct mesh* mesh) {
    return mesh->n_vertices;
}

size_t mesh_n_faces(const struct mesh* mesh) {
    return mesh->n_faces;
}

struct vector mesh_get_vertex(const struct mesh* mesh, size_t i) {
    return mesh->vertices[i];
}

struct face mesh_get_face(const struct mesh* mesh, size_t i) {
    return mesh->faces[i];
}

const struct aabb* mesh_get_aabb(const struct mesh* mesh) {
    return &mesh->aabb;
}
