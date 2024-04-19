/*
 * @author Ethan Uppal
 * @copyright Copyright (C) 2024 Ethan Uppal. All rights reserved.
 */

#pragma once

/** Returns a dynamically-allocated value of type `T*` to be used as a dynamic
 * array, sets `__len` to zero, and sets `__cap` to an initial capacity. */
#define gd_dynamic_new(T, __len, __cap)                                        \
    (__len = 0, __cap = 16, malloc(sizeof(T) * (__cap)))

#define gd_dynamic_push(__arrptr, __len, __cap, __newelem)                     \
    do {                                                                       \
        if ((__len) + 1 >= (__cap)) {                                          \
            __cap *= 2;                                                        \
            *(__arrptr) = realloc(*__arrptr, sizeof(*(__arrptr)) * (__cap));   \
            if (!*(__arrptr)) {                                                \
                exit(1);                                                       \
            }                                                                  \
        }                                                                      \
        (*(__arrptr))[(__len)++] = (__newelem);                                \
    } while (0)
