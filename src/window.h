/*
 * @author Ethan Uppal
 * @copyright Copyright (C) 2024 Ethan Uppal. All rights reserved.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/** A frame for drawing. */
struct frame {
    size_t width;      ///< Frame width in pixels.
    size_t height;     ///< Frame height in pixels.
    uint32_t* buffer;  ///< Frame buffer as RBG values, `0xAARRGGBB` where `A`
                       ///< are alpha bits, and so on.
};

/** Displays a window with title `title`, width `width`, height `height`, and
 * continuously calls `callback`, blocking until the callback returns `false`.
 */
void window_display(const char* title, size_t width, size_t height,
    bool callback(const struct frame*));
