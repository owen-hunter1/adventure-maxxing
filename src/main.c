#include "game.h"
#include <wchar.h>

int main(void){

    Game game = {0};

    if(!game_init(&game)){
        game_close(&game);
        return 1;
    }

    while(game.running){
        game_handle_events(&game);
        game_update(&game, (1.0f/60.0f));
        game_render(&game);
    }
    
    game_close(&game);

    return 0;

}
