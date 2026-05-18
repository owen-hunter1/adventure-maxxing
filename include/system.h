#ifndef SYSTEM_H
#define SYSTEM_H

#include "world.h"
#include <SDL2/SDL_render.h>

void system_movement(World *world, float dt);
void system_physics(World *world, float dt);
void system_render(World *world, SDL_Renderer *renderer, float alpha);

#endif
