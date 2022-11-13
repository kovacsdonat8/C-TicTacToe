#include <stdio.h>
#include "base.h"
#include "menu.h"

int main(void){
    Game game;
    init_game(&game);
    main_menu(&game);
    exit_game(&game);
    return 0;
}