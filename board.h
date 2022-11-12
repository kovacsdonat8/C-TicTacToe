#ifndef AMOBA_NHF_BOARD_H
#define AMOBA_NHF_BOARD_H

#include "base.h"
#include <stdbool.h>

void board_size(Game *g);
void print_board(Game *g);
bool is_board_full(Game *g);
bool is_game_won(Game *g);
char get_mark(Game *g, int row, int col);

#endif //AMOBA_NHF_BOARD_H
