#ifndef WORLD_H
#define WORLD_H

#include <SDL2/SDL_render.h>
#include <stdint.h>


typedef struct{
    float x, y;
    float vx, vy;
} Entity;

typedef struct{
    Entity *entities;
    int count;
    int capacity;
}World;

void world_init(World *world);
void world_update(World *world, float dt);
void world_render(World *world, SDL_Renderer *renderer, float alpha);
void world_add_entity(World *world, Entity entity);
void world_destroy(World *world);

#endif
