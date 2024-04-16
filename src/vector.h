/*
 * @author Ethan Uppal
 * @copyright Copyright (C) 2024 Ethan Uppal. All rights reserved.
 */

#pragma once

typedef double scalar_t;
#define SCALAR_EPSILON 2.22e-16

struct vector {
    scalar_t x;
    scalar_t y;
    scalar_t z;
};

struct vector v_add(struct vector a, struct vector v);
struct vector v_sub(struct vector a, struct vector b);
struct vector v_scale(struct vector a, scalar_t c);
scalar_t v_dot(struct vector a, struct vector b);
struct vector v_cross(struct vector a, struct vector b);
