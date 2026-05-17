#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <SDL2/SDL.h>

typedef struct{
    bool running;
    int width;
    int height;
    SDL_Window *window;
    SDL_Renderer *renderer;
} Game;

bool game_init(Game *game);
void game_handle_events(Game *game);
void game_update(Game *game, float dt);
void game_render(Game *game);
void game_close(Game *game);

#endif
