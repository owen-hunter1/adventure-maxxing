#ifndef WORLD_H
#define WORLD_H

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
void world_destroy(World *world);

#endif
