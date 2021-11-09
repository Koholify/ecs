#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct GraphicPointers {
    int width;
    int height;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* screenSurface;
} GraphicPointers;

GraphicPointers InitGraphics(const char* windowTitle, int width, int height);
void GraphicsClose(GraphicPointers pointers);

SDL_Texture* Graphics_LoadTexture(const char* string, SDL_Renderer* renderer);

#endif /* _GRAPHICS_H */ 
