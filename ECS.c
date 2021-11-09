#include "ECS.h"

static void Entity_Free(Entity* entity) {
    for (size_t i = 0; i < ArrayList_Length(entity->componentList); i++) {
        Component* comp = (Component*)ArrayList_Get(entity->componentList, i);
        if(comp->type == COMPONENT_RENDERABLE) {
            CRenderable_Free((CRenderable*)(comp->handle));
        }
        free(comp->handle);
    }
    ArrayList_Free(entity->componentList);
    free(entity);
}

static void World_RemoveEntity(World* world, size_t entityId) {
    for(size_t i = 0; i < ArrayList_Length(world->entityList); i++) {
        Entity* entity = *((Entity**) ArrayList_Get(world->entityList, i));
        if(entity->id == entityId) {
            ArrayList_RemoveAt(world->entityList, i);
            Entity_Free(entity); 
            return;
        }
    }
}

static void Remove_Dead_Entities(World* world) {
    Entity* entity;
    for(size_t i = 0; i < World_GetEntityCount(world); i++) {
        entity = World_GetEntityByIndex(world, i);
        if(entity->isAlive == 0) {
            World_RemoveEntity(world, entity->id);
            i--;
        }
    }
}

World* World_Create(size_t maxEntities) {
    World* world = (World*) malloc(sizeof(World));
    world->entityList = ArrayList_Create(maxEntities, sizeof(Entity*));
    world->updateFunctionsList = ArrayList_Create(128, sizeof(UpdateFunction));
    return world;
}

void World_Free(World* world) {
    for(size_t i = 0; i < world->entityList->size; i++) {
        Entity_Free(*((Entity**)ArrayList_Get(world->entityList, i)));
    }
    ArrayList_Free(world->entityList);
    ArrayList_Free(world->updateFunctionsList);
}

void World_AddUpdateFunction(World* world, UpdateFunction func) {
    ArrayList_Add(world->updateFunctionsList, &func);
}

void World_AddEntity(World* world, Entity** entity) {
    ArrayList_Add(world->entityList, entity);
}

Entity* World_AddNewEntity(World* world, unsigned int tag) {
    Entity* entity = Entity_Create(tag);
    World_AddEntity(world, &entity);
    return entity;
}

Entity* World_GetEntity(World* world, size_t entityId) {
    for(size_t i = 0; i < ArrayList_Length(world->entityList); i++) {
        Entity* entity = *((Entity**) ArrayList_Get(world->entityList, i));
        if(entity->id == entityId) {
            return entity;
        }
    }
    return NULL;
}

size_t World_GetEntityCount(World* world) {
    return ArrayList_Length(world->entityList);
}

Entity* World_GetEntityByIndex(World* world, size_t index) {
    return *((Entity**) ArrayList_Get(world->entityList, index));
}

void World_Update(World* world) {
    for(size_t i = 0; i < ArrayList_Length(world->updateFunctionsList); i++) {
        UpdateFunction *func = (UpdateFunction*)ArrayList_Get(world->updateFunctionsList, i);
        (*func)(world);
    }

    Remove_Dead_Entities(world);
}


Entity* Entity_Create(unsigned int tag) {
    static size_t index = 0;
    Entity* entity = (Entity*) malloc(sizeof(Entity));
    entity->id = ++index;
    entity->tag = tag;
    entity->isAlive = 1;
    entity->componentList = ArrayList_Create(32, sizeof(Component));
    return entity;
}



void Entity_Destroy(Entity* entity) {
    entity->isAlive = 0;
}

void Entity_AddTag(Entity* entity, Tag tag) {
    entity->tag = entity->tag | tag;
}

int Entity_HasTag(Entity* entity, Tag tag) {
    return entity->tag & tag;
}

void Entity_RemoveTag(Entity* entity, Tag tag) {
    entity->tag = entity->tag & (~tag);
}

void Entity_AddComponent(Entity* entity, Component* comp) {
    if(!Entity_HasComponent(entity, comp->type)) {
        ArrayList_Add(entity->componentList, comp);
    }
}

int Entity_HasComponent(Entity* entity, ComponentType comp) {
    for(size_t i = 0; i < ArrayList_Length(entity->componentList); i++) {
        if (((Component*)ArrayList_Get(entity->componentList, i))->type == comp) {
            return 1;
        }
    }
    return 0;
}

void Entity_RemoveComponent(Entity* entity, ComponentType comp) {
    for(size_t i = 0; i < ArrayList_Length(entity->componentList); i++) {
        if (((Component*)ArrayList_Get(entity->componentList, i))->type == comp) {
            Component* component = (Component*)ArrayList_Get(entity->componentList, i);
            free(component->handle);
            ArrayList_RemoveAt(entity->componentList, i);
        }
    }
}