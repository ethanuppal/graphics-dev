// Copyright (C) 2024 Ethan Uppal. All rights reserved.

#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include "window.h"
#include "render.h"
#include "fps.h"

#define TARGET_FPS 60

struct view {
    struct mesh** meshes;
    size_t mesh_count;
    struct fps fps;
};

bool callback(const struct frame* frame, void* user_data) {
    static double radians = 0;

    struct view* view = (struct view*)user_data;

    const double time_dilate = ((double)TARGET_FPS / fps_current(&view->fps));

    struct camera c;
    c.pos = (struct vector){2 * cos(radians), 0.5, 2 * sin(radians)};
    c.focus = (struct vector){-2 * cos(radians), -0.5, -2 * sin(radians)};
    c.vb_width = 2;
    c.vb_height = 2;
    v_normalize(&c.focus);

    render(frame, view->meshes, view->mesh_count, &c);

    radians += 0.01 * time_dilate;

    fps_hold(&view->fps);
    fps_auto_adjust(&view->fps);

    return true;
}

int main(int argc, const char* argv[]) {
    if (argc != 2) {
        fprintf(stderr,
            "usage: %s <name> where <name>.txt is a model in 'models/'\n",
            argv[0]);
        return 1;
    }

    char buffer[200];
    snprintf(buffer, sizeof(buffer), "models/%s.txt", argv[1]);
    FILE* f = fopen(buffer, "r");
    if (!f) {
        fprintf(stderr, "error: file %s does not exist\n", buffer);
        return 1;
    }
    struct mesh* mesh = mesh_load(f);
    if (!mesh) {
        fprintf(stderr, "error: could not load mesh: %s\n", mesh_load_error());
        return 1;
    }
    fclose(f);

    struct mesh* meshes[] = {mesh};

    struct view view;
    view.meshes = meshes;
    view.mesh_count = sizeof(meshes) / sizeof(*meshes);
    view.fps = fps_make(60);

    window_display("Test", 400, 400, callback, &view);

    return 0;
}
