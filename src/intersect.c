/*
 * @author Ethan Uppal
 * @copyright Copyright (C) 2024 Ethan Uppal. All rights reserved.
 */

#include "intersect.h"

scalar_t min(scalar_t x, scalar_t y) {
    return x < y ? x : y;
}

scalar_t max(scalar_t x, scalar_t y) {
    return x > y ? x : y;
}

bool intersect_aabb(struct vector src, struct vector dir,
    const struct aabb* aabb) {
    // Ripped from https://gamedev.stackexchange.com/a/18459

    scalar_t dirfrac_x = 1.0 / dir.x;
    scalar_t dirfrac_y = 1.0 / dir.y;
    scalar_t dirfrac_z = 1.0 / dir.z;

    scalar_t t1 = (aabb->min.x - src.x) * dirfrac_x;
    scalar_t t2 = (aabb->max.x - src.x) * dirfrac_x;
    scalar_t t3 = (aabb->min.y - src.y) * dirfrac_y;
    scalar_t t4 = (aabb->max.y - src.y) * dirfrac_y;
    scalar_t t5 = (aabb->min.z - src.z) * dirfrac_z;
    scalar_t t6 = (aabb->max.z - src.z) * dirfrac_z;

    float tmin = max(max(min(t1, t2), min(t3, t4)), min(t5, t6));
    float tmax = min(min(max(t1, t2), max(t3, t4)), max(t5, t6));

    if (tmax < 0) {
        return false;
    }

    // if tmin > tmax, ray doesn't intersect AABB
    if (tmin > tmax) {
        return false;
    }

    return true;
}

bool intersect_face(struct vector src, struct vector dir,
    const struct mesh* mesh, size_t face_i, scalar_t* dist,
    struct vector* pos) {
    // https://en.wikipedia.org/wiki/Möller–Trumbore_intersection_algorithm
    // [dir edge1 edge2](t u v) = src - face_a

    scalar_t epsilon = SCALAR_EPSILON;

    struct face face = mesh_get_face(mesh, face_i);
    struct vector face_a = mesh_get_vertex(mesh, face.v1);
    struct vector face_b = mesh_get_vertex(mesh, face.v2);
    struct vector face_c = mesh_get_vertex(mesh, face.v3);

    struct vector edge1 = v_sub(face_b, face_a);
    struct vector edge2 = v_sub(face_c, face_a);
    struct vector ray_cross_e2 = v_cross(dir, edge2);
    scalar_t det = v_dot(edge1, ray_cross_e2);

    // ray is parallel : dir || edge1 or dir || edge2 so det = 0
    if (det > -epsilon && det < epsilon) return false;

    // u = det [dir (src - face_a) edge2] * invde
    scalar_t inv_det = 1.0 / det;
    struct vector s = v_sub(src, face_a);
    scalar_t u = inv_det * v_dot(s, ray_cross_e2);

    if (u < 0 || u > 1) return false;

    struct vector s_cross_e1 = v_cross(s, edge1);
    scalar_t v = inv_det * v_dot(dir, s_cross_e1);

    if (v < 0 || u + v > 1) return false;

    *dist = inv_det * v_dot(edge2, s_cross_e1);

    if (*dist > epsilon) {
        *pos = v_add(src, v_scale(dir, *dist));
        return true;
    } else {
        return false;
    }
}
