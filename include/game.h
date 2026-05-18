#ifndef GAME_H
#define GAME_H

#include "world.h"
#include <stdbool.h>
#include <SDL2/SDL.h>

typedef struct{
    bool running;
    int width;
    int height;
    SDL_Window *window;
    SDL_Renderer *renderer;
    World world;
} Game;

bool game_init(Game *game);
void game_close(Game *game);
void game_run(Game *game);

#endif
