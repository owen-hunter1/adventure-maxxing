#include "system.h"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

void system_movement(World *world, float dt){
    for(int i = 0; i < world->count; i++){
        Entity *e = &world->entities[i];

        e->x += e->vx * dt;
        e->y += e->vy * dt;

        float bounceLoss = -0.85f;

        if(e->y >= 458){
            e->y = 458;
            e->vy *= bounceLoss;

            if(fabsf(e->vy) < 0.05f){
                e->vy = 0;
            }
        }
    }
}

void system_physics(World *world, float dt){
    for(int i = 0; i < world->count; i++){
        Entity *e = &world->entities[i];

        const float gravity = 500.0f;
        const float drag = 0.01f;

        e->vy += gravity * dt;

        e->vy -= e->vy * drag * dt;
    }
}

void system_render(World *world, SDL_Renderer *renderer, float alpha){
    for(int i = 0; i < world->count; i++){
        Entity *e = &world->entities[i];

        SDL_Rect rect = {
            (int)e->x,
            (int)e->y,
            32,
            32
        };

        SDL_SetRenderDrawColor(renderer, 225, 0, 0, 225);
        SDL_RenderFillRect(renderer, &rect);
    }
}
