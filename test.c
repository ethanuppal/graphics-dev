/*
 * @author Ethan Uppal
 * @copyright Copyright (C) 2024 Ethan Uppal. All rights reserved.
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "mesh.h"

#ifdef TEST
    #define MAIN main
#else
    #define MAIN not_main
#endif

#define assert_equal(exp, act)                                                 \
    test_assert_equal((exp) == (act), #exp, #act, __FUNCTION__, __LINE__)

#define assert_true(val) test_assert_true(val, #val, __FUNCTION__, __LINE__)

void test_assert_equal(bool result, const char* exp, const char* act,
    const char* func, int line) {
    if (!result) {
        fprintf(stderr, "%s: assert_equal failed line %d: %s != %s\n", func,
            line, exp, act);
        exit(1);
    }
}

void test_assert_true(bool result, const char* expr, const char* func,
    int line) {
    if (!result) {
        fprintf(stderr, "%s: assert_true failed at line %d: %s == false\n",
            func, line, expr);
        exit(1);
    }
}

void test_load_mesh(void) {
    FILE* f = fopen("models/tri.txt", "r");
    struct mesh* mesh = mesh_load(f);
    fclose(f);

    assert_equal(3, mesh_n_vertices(mesh));
    assert_equal(1, mesh_n_faces(mesh));

    struct vector v1 = mesh_get_vertex(mesh, 0);
    assert_equal(0.0, v1.x);
    assert_equal(0.0, v1.y);
    assert_equal(0.0, v1.z);

    struct vector v2 = mesh_get_vertex(mesh, 1);
    assert_equal(1.0, v1.x);
    assert_equal(1.0, v1.y);
    assert_equal(0.0, v1.z);

    struct vector v3 = mesh_get_vertex(mesh, 2);
    assert_equal(2.0, v1.x);
    assert_equal(0.0, v1.y);
    assert_equal(0.0, v1.z);

    struct face face = mesh_get_face(mesh, 0);
    assert_equal(0, face.v1);
    assert_equal(0, face.v2);
    assert_equal(0, face.v2);

    mesh_destroy(mesh);
}

int MAIN(void) {
    test_load_mesh();
    fprintf(stderr, "All test passed!\n");
    return 0;
}
