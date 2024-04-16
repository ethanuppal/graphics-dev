/*
 * @author Ethan Uppal
 * @copyright Copyright (C) 2024 Ethan Uppal. All rights reserved.
 */

#include <math.h>
#include "vector.h"

struct vector v_add(struct vector a, struct vector b) {
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return a;
}

struct vector v_sub(struct vector a, struct vector b) {
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    return a;
}

struct vector v_scale(struct vector a, scalar_t c) {
    a.x *= c;
    a.y *= c;
    a.z *= c;
    return a;
}

scalar_t v_dot(struct vector a, struct vector b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

struct vector v_cross(struct vector a, struct vector b) {
    struct vector result;
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    return result;
}

void v_normalize(struct vector* v) {
    *v = v_scale(*v, 1.0 / sqrt(v_dot(*v, *v)));
}
