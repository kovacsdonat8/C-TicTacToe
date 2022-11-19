#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "base.h"
#include "menu.h"

int main(void){
    Game game;
    init_game(&game);
    srand(time(0));
    main_menu(&game);
    exit_game(&game);
    return 0;
}