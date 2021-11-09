#ifndef _COMPONENT_TYPES_H
#define _COMPONENT_TYPES_H

#include <SDL2/SDL.h>

typedef enum {
    COMPONENT_TRANSFORM,
    COMPONENT_RENDERABLE,
} ComponentType;

typedef struct Component {
    ComponentHandle handle;
    ComponentType type;
} Component;

typedef struct CTransform {
    float x;
    float y;
    float dx;
    float dy;
} CTransform;

typedef struct CRenderable {
    SDL_Rect rect;
    SDL_Texture* texture;
} CRenderable;

Component* CTransform_Create();
Component* CRenderable_Create();
void CRenderable_Free(CRenderable* comp);

#endif