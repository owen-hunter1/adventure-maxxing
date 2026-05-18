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

    Entity player = {320, 0, 0,0};
    world_add_entity(world, player);
}

void world_update(World *world, float dt){
    system_movement(world, dt);
    system_physics(world, dt);
}

void world_render(World *world, SDL_Renderer *renderer, float alpha){
    system_render(world, renderer, alpha);
}

void world_add_entity(World *world, Entity entity){
    if(world->count < world->capacity){
        world->entities[world->count] = entity;
        world->count++;
    }
}

void world_destroy(World *world){
    if(!world) return;

    free(world->entities);
    world->entities = NULL;
    world->count = 0;
    world->capacity = 0;
}
