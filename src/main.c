#include "game.h"

int main(void){

    Game game = {0};

    if(!game_init(&game)){
        game_close(&game);
        return 1;
    }

    game_run(&game);
    game_close(&game);

}
