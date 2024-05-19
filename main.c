// Copyright (C) 2024 Ethan Uppal. All rights reserved.

#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include "window.h"
#include "render.h"
#include "fps.h"

#define TARGET_FPS 60
#define lengthof(a) (sizeof(a) / sizeof(*(a)))

struct view {
    struct scene scene;
    struct camera camera;
    scalar_t camera_angle;
    struct fps fps;
};

void on_event(const SDL_Event* event, void* user_data) {
    // only handle key events
    if (event->type != SDL_KEYDOWN && event->type != SDL_KEYUP) {
        return;
    }

    struct view* view = (struct view*)user_data;

    // TODO:
}

bool draw(const struct frame* frame, void* user_data) {
    static double radians = 0;

    struct view* view = (struct view*)user_data;

    const double time_dilate = ((double)TARGET_FPS / fps_current(&view->fps));

    view->camera.pos = (struct vector){2 * cos(radians), 0.5, 2 * sin(radians)};
    view->camera.focus = (struct vector){
        -2 * cos(radians), -0.5, -2 * sin(radians)};
    v_normalize(&view->camera.focus);

    render(frame, &view->scene, &view->camera);

    radians += 0.02 * time_dilate;

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

    struct light lights[] = {{.pos = (struct vector){0, 0, 0}, .intensity = 1}};

    struct camera camera;
    camera.pos = (struct vector){2, 0.5, 0};
    camera.focus = (struct vector){-2, -0.5, 0};
    camera.vb_width = 2;
    camera.vb_height = 2;
    v_normalize(&camera.focus);

    struct view view;
    view.scene.meshes = meshes;
    view.scene.mesh_count = lengthof(meshes);
    view.scene.lights = lights;
    view.scene.light_count = lengthof(lights);
    view.camera = camera;
    view.fps = fps_make(60);

    window_display("Test", 400, 400, on_event, draw, &view);

    return 0;
}
