/*
 * @author Ethan Uppal
 * @copyright Copyright (C) 2024 Ethan Uppal. All rights reserved.
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "mesh.h"
#include "intersect.h"

#ifdef TEST
    #define MAIN main
#else
    #define MAIN not_main
#endif

#define assert_equal(exp, act)                                                 \
    test_assert_equal((exp) == (act), #exp, #act, __FUNCTION__, __LINE__)

#define assert_true(val)                                                       \
    test_assert_true(val, #val, "true", __FUNCTION__, __LINE__)

#define assert_false(val)                                                      \
    test_assert_true(!(val), #val, "false", __FUNCTION__, __LINE__)

void test_assert_equal(bool result, const char* exp, const char* act,
    const char* func, int line) {
    if (!result) {
        fprintf(stderr,
            "%s: assert_equal failed %s:%d: %s is not equal to %s\n", func,
            __FILE__, line, act, exp);
        exit(1);
    }
}

void test_assert_true(bool result, const char* expr, const char* type,
    const char* func, int line) {
    if (!result) {
        fprintf(stderr, "%s: assert_%s failed at %s:%d: %s is not %s\n", func,
            type, __FILE__, line, expr, type);
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
    assert_equal(1.0, v2.x);
    assert_equal(1.0, v2.y);
    assert_equal(0.0, v2.z);

    struct vector v3 = mesh_get_vertex(mesh, 2);
    assert_equal(2.0, v3.x);
    assert_equal(0.0, v3.y);
    assert_equal(0.0, v3.z);

    struct face face = mesh_get_face(mesh, 0);
    assert_equal(0, face.v1);
    assert_equal(1, face.v2);
    assert_equal(2, face.v3);
    assert_equal(0xFF0000, face.color);

    const struct aabb* aabb = mesh_get_aabb(mesh);
    assert_equal(0, aabb->min.x);
    assert_equal(0, aabb->min.y);
    assert_equal(0, aabb->min.z);
    assert_equal(2, aabb->max.x);
    assert_equal(1, aabb->max.y);
    assert_equal(0, aabb->max.z);

    mesh_destroy(mesh);
}

void test_intersect_aabb(void) {
    struct aabb test_aabb = {{-1.0, -1.0, -1.0}, {1.0, 1.0, 1.0}};

    /*
       +----+
       |    |   <-
       +----+
    */
    struct vector ray_src = {2.0, 0.0, 0.0};
    struct vector ray_dir = {-1.0, 0.0, 0.0};
    assert_true(intersect_aabb(ray_src, ray_dir, &test_aabb));

    /*
       +----+
       | -> |
       +----+
    */
    ray_src.x = 0.0;
    ray_src.y = 0.0;
    ray_src.z = 0.0;
    ray_dir.x = 1.0;
    ray_dir.y = 0.0;
    ray_dir.z = 0.0;
    assert_true(intersect_aabb(ray_src, ray_dir, &test_aabb));

    /*
                ->
       +----+
       |    |
       +----+
    */
    ray_src.x = 2.0;
    ray_src.y = 2.0;
    ray_src.z = 2.0;
    ray_dir.x = 0.0;
    ray_dir.y = 0.0;
    ray_dir.z = 1.0;
    assert_false(intersect_aabb(ray_src, ray_dir, &test_aabb));
}

void test_intersect_face(void) {
    FILE* f = fopen("models/test1.txt", "r");
    struct mesh* mesh = mesh_load(f);
    fclose(f);

    assert_equal(3, mesh_n_vertices(mesh));
    assert_equal(1, mesh_n_faces(mesh));

    struct vector src;
    src.x = 0;
    src.y = 0;
    src.z = 0;

    struct vector dir;
    dir.x = 0;
    dir.y = 0;
    dir.z = 1;

    scalar_t dist;
    struct vector pos;
    assert_true(intersect_face(src, dir, mesh, 0, &dist, &pos));

    src.x = 10;
    assert_false(intersect_face(src, dir, mesh, 0, &dist, &pos));

    mesh_destroy(mesh);
}

int MAIN(void) {
    test_load_mesh();
    test_intersect_aabb();
    test_intersect_face();
    fprintf(stderr, "All test passed!\n");
    return 0;
}
