/*
 * @author Ethan Uppal
 * @copyright Copyright (C) 2024 Ethan Uppal. All rights reserved.
 */

#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <SDL_events.h>  // SDL_Event

/** A frame for drawing. */
struct frame {
    size_t width;      ///< Frame width in pixels.
    size_t height;     ///< Frame height in pixels.
    uint32_t* buffer;  ///< Frame buffer as RBG values, `0xAARRGGBB` where `A`
                       ///< are alpha bits, and so on.
};

/** Displays a window with title `title`, width `width`, height `height`, and
 * continuously calls `draw`, blocking until this callback returns `false`.
 * The `on_event` callback is invoked whenever there is an event.
 */
void window_display(const char* title, size_t width, size_t height,
    void on_event(const SDL_Event*, void*),
    bool draw(const struct frame*, void*), void* user_data);
