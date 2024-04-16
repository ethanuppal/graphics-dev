// Copyright (C) 2024 Ethan Uppal. All rights reserved.

#include <stdio.h>
#include "window.h"
#include "render.h"

struct scene {
    struct mesh** meshes;
    size_t mesh_count;
};

bool callback(const struct frame* frame, void* user_data) {
    static double radians = 0;

    struct camera c;
    c.pos = (struct vector){0, 0, 0};
    c.focus = (struct vector){0, 0, 1};
    c.h_hat = (struct vector){0, 1, 0};
    c.vb_width = 2;
    c.vb_height = 2;

    struct scene* scene = (struct scene*)user_data;

    render(frame, scene->meshes, scene->mesh_count, c);

    radians += 0.01;
    return true;
}

int main(int argc, const char* argv[]) {
    if (argc != 2) {
        fprintf(stderr,
            "usage: %s <name> where <name>.txt is a model in models/\n",
            argv[0]);
        return 1;
    }

    char buffer[200];
    snprintf(buffer, sizeof(buffer), "models/%s.txt", argv[1]);
    FILE* f = fopen(buffer, "r");
    if (!f) {
        fprintf(stderr, "error: file %s does not exist", buffer);
        return 1;
    }
    struct mesh* mesh = mesh_load(f);
    if (!mesh) {
        fprintf(stderr, "error: could not load mesh: %s\n", mesh_load_error());
        return 1;
    }
    fclose(f);

    struct mesh* meshes[] = {mesh};

    struct scene scene;
    scene.meshes = meshes;
    scene.mesh_count = sizeof(meshes) / sizeof(*meshes);

    window_display("Test", 400, 400, callback, &scene);

    return 0;
}
