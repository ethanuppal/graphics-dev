// Copyright (C) 2024 Ethan Uppal. All rights reserved.

#include <stdio.h>
#include "window.h"
#include "render.h"

struct scene {
    struct mesh** meshes;
    size_t mesh_count;
};

bool callback(const struct frame* frame, void* user_data) {
    struct view_box vb;
    vb.min_x = -1;
    vb.min_y = -1;
    vb.max_x = 1;
    vb.max_y = 1;
    vb.z_focus = 0;

    struct scene* scene = (struct scene*)user_data;

    render(frame, scene->meshes, scene->mesh_count, vb);

    return true;
}

int main() {
    FILE* f = fopen("models/test1.txt", "r");
    struct mesh* mesh = mesh_load(f);
    fclose(f);

    struct mesh* meshes[] = {mesh};

    struct scene scene;
    scene.meshes = meshes;
    scene.mesh_count = sizeof(meshes) / sizeof(*meshes);

    window_display("Test", 400, 400, callback, &scene);

    return 0;
}
