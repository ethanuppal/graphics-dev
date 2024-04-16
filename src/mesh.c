/*
 * @author Ethan Uppal
 * @copyright Copyright (C) 2024 Ethan Uppal. All rights reserved.
 */

#include "mesh.h"
#include <stdlib.h>

struct mesh {
    size_t n_vertices;
    size_t n_faces;
    struct vector* vertices;
    struct face* faces;
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
        if (fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z) < 3) {
            exit(1);
        }
        printf("%f %f %f\n", vertex.x, vertex.y, vertex.z);
        mesh->vertices[i] = vertex;
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
