#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include "game.h"

static const int WINDOW_WIDTH = 640;
static const int WINDOW_HEIGHT = 480;

//initialize SDL window and renderer
bool game_init(Game *game){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return false;
    }

    game->width = WINDOW_WIDTH;
    game->height = WINDOW_HEIGHT;

    game->window = SDL_CreateWindow("Adventure Max", SDL_WINDOWPOS_UNDEFINED, game->height, game->width, WINDOW_HEIGHT, 0);

    if(!game->window){
        SDL_Log("Couldn't create SDL Window: %s", SDL_GetError());
        return false;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED);

    if(!game->renderer){
        SDL_Log("Couldn't create SDL Renderer: %s", SDL_GetError());
        return false;
    }

    game->running = true;

    return true;
}


void game_handle_events(Game *game){
    SDL_Event event;

    while (SDL_PollEvent(&event)){
        switch (event.type){
            case SDL_QUIT:
                game->running = false;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        game->running = false;
                        break;
                }
                break;
        }
    }
}

void game_update(Game *game, float dt){

}

void game_render(Game *game){

}

//handle game shutdown
void game_close(Game *game){
    if(game->renderer){
        SDL_DestroyRenderer(game->renderer);
    }

    if(game->window){
        SDL_DestroyWindow(game->window);
    }

    SDL_Quit();
}
