// Copyright (C) 2024 Ethan Uppal. All rights reserved.

#include <time.h>
#include "window.h"

bool callback(const struct frame* frame) {
    static size_t rolling = 0;
    for (size_t j = 0; j < frame->height; j++) {
        for (size_t i = 0; i < frame->width; i++) {
            frame->buffer[j * frame->width + i] =
                (i + rolling) << 12 + (j + rolling) % (1 << 13 - 1);
        }
    }
    rolling++;
    return true;
}

int main() {
    window_display("Test", 400, 400, callback);
    return 0;
}
