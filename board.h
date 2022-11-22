#ifndef AMOBA_NHF_BOARD_H
#define AMOBA_NHF_BOARD_H

#include "base.h"
#include <stdbool.h>

bool create_board(Game *g);
void destroy_board(Game *g);
bool write_game(Game *g);
bool read_game(Game *g);
void board_size(Game *g);
void print_board(Game *g);
bool is_board_full(Game *g);
bool is_game_won(Game *g);
int longest_line(Game *g, int row, int col);
bool is_board_empty(Game *g);
bool has_neighbour(Game *g, int row, int col);

#endif //AMOBA_NHF_BOARD_H
