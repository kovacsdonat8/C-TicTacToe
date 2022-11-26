#ifndef AMOBA_NHF_BOARD_H
#define AMOBA_NHF_BOARD_H

#include "base.h"
#include <stdbool.h>

bool create_board(Game *g);
void destroy_board(Game *g);
bool save_game(Game *g);
bool load_game(Game *g);
void board_size(Game *g);
void print_board(Game *g);
bool is_board_full(Game *g);
bool is_game_won(Game *g);
void evaluate_board(Game *g, int *row, int *col, char sign);
bool is_board_empty(Game *g);
bool has_neighbour(Game *g, int row, int col);

#endif //AMOBA_NHF_BOARD_H
