#ifndef AMOBA_NHF_MOVES_H
#define AMOBA_NHF_MOVES_H

#include <stdbool.h>

#include "base.h"
#include "board.h"

bool human_move(Game *g, int *row, int *col);
bool mark_player_move(Game *g, int row, int col);
bool computer_move_random(Game *g, int *row, int *col);
bool computer_move_offensive(Game *g, int *row, int *col);
bool computer_move_defensive(Game *g, int *row, int *col);
bool next_move(Game *g, int *row, int *col);

#endif //AMOBA_NHF_MOVES_H
