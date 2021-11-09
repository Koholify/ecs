#include "Graphics.h"

GraphicPointers InitGraphics(const char* windowTitle, int width, int height) {
    GraphicPointers pointers;
    pointers.height = height;
    pointers.width = width;

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("SDL init failed! Error: %s", SDL_GetError());
        abort();
    } else {
        pointers.window = SDL_CreateWindow(
            windowTitle,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width,
            height,
            SDL_WINDOW_SHOWN
        );
        if(pointers.window == NULL) {
            printf("SDL window failed! Error: %s", SDL_GetError());
            abort();
        } else {
            pointers.renderer = SDL_CreateRenderer(
                pointers.window,
                -1,
                SDL_RENDERER_ACCELERATED
            );
            if(pointers.renderer == NULL) {
                printf("SDL renderer init failed! Error: %s", SDL_GetError());
                abort();
            } else {
                SDL_SetRenderDrawColor(pointers.renderer,
                0x00, 0x00, 0x00, 0xFF);

                int imgFlags = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags) & imgFlags)) {
                    printf("SDL init failed! Error: %s", SDL_GetError());
                    abort();
                } else {
                    pointers.screenSurface = SDL_GetWindowSurface(pointers.window);
                }
            }
        }
    }

    return pointers;
}

void GraphicsClose(GraphicPointers pointers) {
    SDL_DestroyWindow(pointers.window);
    SDL_DestroyRenderer(pointers.renderer);
    IMG_Quit();
    SDL_Quit();
}

SDL_Texture* Graphics_LoadTexture(const char* string, SDL_Renderer* renderer) {
    SDL_Texture* texture = NULL;
    SDL_Surface* surface = IMG_Load(string);
    if(surface == NULL) {
        printf("ERROR LOADING %s! Error: %s\n", string, IMG_GetError());
    } else {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if(texture == NULL) {
            printf("ERROR CONVERTING SURFACE %s! Error: %s\n", string, SDL_GetError());
        }

        SDL_FreeSurface(surface);
    }

    return texture;
}