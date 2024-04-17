/*
 * @author Ethan Uppal
 * @copyright Copyright (C) 2024 Ethan Uppal. All rights reserved.
 */

#include <sys/time.h>
#include "fps.h"

static double get_time(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;
}

struct fps fps_make(int target) {
    struct fps fps;
    fps.old_target = target;
    fps.target = target;
    fps.current = target;
    fps.last_time = get_time() - 1.0 / target;
    fps.below_count = 0;
    fps.fps_changes = 0;
    return fps;
}

void fps_hold(struct fps* fps) {
    double now_time = 0.0;
    double time_delay = 1.0 / fps->target;
    while ((now_time = get_time()) - fps->last_time < time_delay) {
        // wait
    }
    fps->current = 1.0 / (now_time - fps->last_time);
    fps->last_time = now_time;
}

void fps_auto_adjust(struct fps* fps) {
    if (fps->current < fps->target) {
        fps->below_count++;
    } else {
        fps->below_count = 0;
    }

    if (fps->below_count > (1 << fps->fps_changes)) {
        fps->target--;
        fps->below_count = 0;
        fps->fps_changes++;
    }
}

int fps_current(const struct fps* fps) {
    return fps->current;
}
