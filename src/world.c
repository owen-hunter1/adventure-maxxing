#include "world.h"
#include "system.h"
#include <SDL2/SDL_log.h>
#include <stdlib.h>

static const int MAX_ENTITIES = 255;

void world_init(World *world){
    world->entities = malloc(sizeof(Entity) * MAX_ENTITIES);
    if (!world->entities) {
        SDL_Log("Failed to allocate world entities");
        world->entities = NULL;
        world->capacity = world->count = 0;
        return;
    }

    world->count = 0;
    world->capacity = MAX_ENTITIES;
}

void world_update(World *world, float dt){
    system_physics(world, dt);
    system_movement(world, dt);
}

void world_destroy(World *world){
    if(!world) return;

    free(world->entities);
    world->entities = NULL;
    world->count = 0;
    world->capacity = 0;
}
