#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "base.h"

/*
void computer_move(){
    char move[5];
    printf("Press enter for computer move (0 for main menu): ");
    scanf("%4s", move);
    if (move[0] == '0'){
        break;
    }
}
*/
bool human_move(Game *g, int *row, int *col){
    char move[5];
    char *p;
    while (true) {
        printf("Enter move (e.g. A5 or 0 for main menu): ");
        scanf("%4s", move);
        p = move;
        if (*p == '0'){
            return false;
        }
        if (*p < 'A' || *p > 'Z') {
            printf("Invalid move!\n");
            continue;
        }
        *row = *p - 'A';
        p++;
        if (*p >= 'A' && *p <= 'Z'){
            *row = (*row + 1) * 26 + (*p - 'A');
            p++;
        }
        *col = atoi(p) - 1;
        if (*row >= g->boardsize || *col < 0 || *col >= g->boardsize){
            printf("Invalid move!\n");
            continue;
        }
        return true;
    }
}

bool player_move(Game *g, int row, int col){
    char sign = g->actual_player == 0 ? g->p1sign : g->p2sign;
    int index = row * g->boardsize + col;
    if (g->board[index] != ' '){
        printf("Invalid move!\n");
        return false;
    }
    g->board[index] = sign;
    return true;
}
