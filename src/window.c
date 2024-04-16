/*
 * @author Ethan Uppal
 * @copyright Copyright (C) 2024 Ethan Uppal. All rights reserved.
 */

#include "window.h"
#include <stdlib.h>
#include <SDL.h>

void window_display(const char* title, size_t width, size_t height,
    bool callback(const struct frame*)) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        exit(1);
    }

    SDL_Window* window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        exit(1);
    }
    SDL_Renderer* renderer = renderer = SDL_CreateRenderer(window, 0,
        SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        exit(1);
    }

    // https://gamedev.stackexchange.com/questions/157604/how-to-get-access-to-framebuffer-as-a-uint32-t-in-sdl2
    SDL_Texture* frame_texture = SDL_CreateTexture(renderer,
        SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    if (!frame_texture) {
        exit(1);
    }

    uint32_t* pixels = malloc(sizeof(*pixels) * width * height);
    if (!pixels) {
        exit(1);
    }

    struct frame frame;
    frame.width = width;
    frame.height = height;
    frame.buffer = pixels;

    bool quit = false;
    SDL_Event event;
    do {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
                break;
            }
        }
        if (!quit) {
            quit = !callback(&frame);
            SDL_UpdateTexture(frame_texture, NULL, pixels,
                width * sizeof(*pixels));
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, frame_texture, NULL, NULL);
            SDL_RenderPresent(renderer);
        }
    } while (!quit);

    free(pixels);
    SDL_DestroyTexture(frame_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
