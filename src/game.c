#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <wchar.h>
#include "game.h"
#include "world.h"

// window size
static const int WINDOW_WIDTH = 640;
static const int WINDOW_HEIGHT = 480;

// fps
static const float TIMESTEP = 1.0f / 60.0f;
static const float MAX_FRAME_TIME = 0.25f;

// function declarations
static void game_update(Game *game, float dt);
static void game_render(Game *game, float alpha);
static void game_handle_events(Game *game);

//initialize SDL window and renderer
bool game_init(Game *game){
    printf("Initializing game...\n");

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return false;
    }

    // set height and width
    game->width = WINDOW_WIDTH;
    game->height = WINDOW_HEIGHT;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    // create window
    game->window = SDL_CreateWindow("Adventure Max", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,game->width, game->height, 0);

    if(!game->window){
        SDL_Log("Couldn't create SDL Window: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }
    // create renderer
    game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(!game->renderer){
        SDL_Log("Couldn't create SDL Renderer: %s", SDL_GetError());
        SDL_DestroyWindow(game->window);
        game->window = NULL;
        SDL_Quit();
        return false;
    }

    game->running = true;

    world_init(&game->world);

    printf("finished initializing game!\n");

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
    world_update(&game->world, dt);
}

void game_render(Game *game, float alpha){
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 255,255);
    SDL_RenderClear(game->renderer);

    //render entities
    world_render(&game->world, game->renderer, alpha);

    SDL_RenderPresent(game->renderer);
}

//game loop
void game_run(Game *game){

    Uint64 previous = SDL_GetPerformanceCounter();
    float lag = 0.0;

    while(game->running){

        Uint64 current = SDL_GetPerformanceCounter();
        float elapsed = (float)(current - previous) / SDL_GetPerformanceFrequency(); // ticks * (seconds / ticks) to convert elapsed ticks to seconds
        
        // cap elapsed time
        if(elapsed > MAX_FRAME_TIME ){
            elapsed = MAX_FRAME_TIME;
        }

        previous = current;
        lag += elapsed;

        // handle game logic
        game_handle_events(game);

        // keeps update fixed
        while (lag >= TIMESTEP) {
            game_update(game,TIMESTEP);
            lag -= TIMESTEP;
        }

        // alpha for position interpolation
        float alpha = lag / TIMESTEP;
        game_render(game, alpha);
    }
}

//handle game shutdown
void game_close(Game *game){

    world_destroy(&game->world);

    if(game->renderer){
        SDL_DestroyRenderer(game->renderer);
    }

    if(game->window){
        SDL_DestroyWindow(game->window);
    }

    SDL_Quit();
}
