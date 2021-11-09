#include "ECS.h"
#include "Graphics.h"
#include "Systems.h"
#include <unistd.h>

int main(int argc, char* args[]) {
    GraphicPointers gPointers = InitGraphics("ECS test", 600, 400);

    World* this = World_Create(1024);
    Entity* entity = World_AddNewEntity(this, TAG_PLAYER);
    for(size_t i = 0; i < 2; i++) {
        World_AddNewEntity(this, TAG_ENEMY);
    }

    World_AddUpdateFunction(this, &System_PrintInfo);

    int running = 1;
    SDL_Event e;
    while(running) {
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                running = 0;
            }
        }

        World_Update(this);

        SDL_RenderClear(gPointers.renderer);

        SDL_RenderPresent(gPointers.renderer);
    }

    World_Free(this);

    GraphicsClose(gPointers);
   
    return 0;
}