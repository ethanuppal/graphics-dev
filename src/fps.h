/*
 * @author Ethan Uppal
 * @copyright Copyright (C) 2024 Ethan Uppal. All rights reserved.
 */

/** An FPS controller. */
struct fps {
    int old_target;    ///< @private The original target FPS;
    int target;        ///< @private The current target delay FPS.
    int current;       ///< @private The most recent FPS.
    double last_time;  ///< @private The most recent time in seconds.
    int below_count;  ///< @private If positive, the number of times the FPS has
                      ///< been below the target.
    int fps_changes;  ///< @private The number of times the FPS has been
                      ///< adjusted.
};

/** Makes a new FPS controller. */
struct fps fps_make(int target);

/** Delays until the target FPS is acheived. */
void fps_hold(struct fps* fps);

/** Automatically lowers FPS based on empirical performance to achieve
 * constancy. */
void fps_auto_adjust(struct fps* fps);

/** The current FPS. */
int fps_current(const struct fps* fps);
