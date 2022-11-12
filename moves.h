#ifndef AMOBA_NHF_MOVES_H
#define AMOBA_NHF_MOVES_H

#include <stdbool.h>

#include "base.h"

bool human_move(Game *g, int *row, int *col);
bool player_move(Game *g, int row, int col);


#endif //AMOBA_NHF_MOVES_H
