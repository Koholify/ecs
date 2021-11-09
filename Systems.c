#include "Systems.h"

void System_PrintInfo(World* world) {
    Entity* entity;
    for(size_t i = 0; i < World_GetEntityCount(world); i++) {
        entity = World_GetEntityByIndex(world, i);
        size_t components = ArrayList_Length(entity->componentList);
        printf("Entity %ld: alive - %d ; tag - %u ; components - %ld\n", entity->id, entity->isAlive, entity->tag, components);
    }
}

void System_Move(World* world) {
    
}