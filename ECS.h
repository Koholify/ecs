#ifndef _ECS_H
#define _ECS_H

#include <stdlib.h>
#include <stdio.h>
#include "ArrayList.h"
#include "ComponentTypes.h"

typedef void* ComponentHandle;
typedef struct World World;

typedef void (*UpdateFunction)(World* world);

typedef enum {
    TAG_PLAYER = 1,
    TAG_ENVIRONMENT = 1 << 1,
    TAG_ENEMY = 1 << 2,
    TAG_ATTACK = 1 << 3,
    TAG_TO_DELETE = 1 << 4,
} Tag;

struct World {
    ArrayList* entityList;
    ArrayList* updateFunctionsList;
};

typedef struct Entity {
    size_t id;
    int isAlive;
    unsigned int tag;
    ArrayList* componentList;
} Entity;

// Create world
World* World_Create(size_t maxEntities);

// Handle deletion of world
void World_Free(World* world);

// Add function to be called on update
void World_AddUpdateFunction(World* world, UpdateFunction func);

// Handling Entities in world
void World_AddEntity(World* world, Entity** entity);
Entity* World_AddNewEntity(World* world, unsigned int tag);
//void World_RemoveEntity(World* world, size_t entityId);
Entity* World_GetEntity(World* world, size_t entityId);
Entity* World_GetEntityByIndex(World* world, size_t index);
size_t World_GetEntityCount(World* world);

// Call on update
void World_Update(World* world);

//Create new entity
Entity* Entity_Create(unsigned int tag);
void Entity_Destroy(Entity* entity);
//void Entity_Free(Entity* entity);


// Deal with tags
void Entity_AddTag(Entity* entity, Tag tag);
int Entity_HasTag(Entity* entity, Tag tag);
void Entity_RemoveTag(Entity* entity, Tag tag);

// Deal with components
void Entity_AddComponent(Entity* entity, Component* comp);
int Entity_HasComponent(Entity* entity, ComponentType comp);
void Entity_RemoveComponent(Entity* entity, ComponentType comp);

#endif