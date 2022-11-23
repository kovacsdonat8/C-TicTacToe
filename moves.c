#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "base.h"
#include "board.h"

bool human_move(Game *g, int *row, int *col){
    char move[100];
    char *p;
    while (true) {
        printf("Enter move (e.g. A5 or 0 for main menu): ");
        input_str(move, sizeof(move));
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

bool computer_move_offensive(Game *g, int *row, int *col){
    char move[100];
    printf("Press enter for computer move (0 for main menu): ");
    input_str(move, sizeof(move));
    if (move[0] == '0') {
        return false;
    }
    //evaluate the board for ourselves
    char sign = g->actual_player == 0 ? g->p1sign : g->p2sign;
    evaluate_board(g, row, col, sign);
    return true;
}

bool computer_move_defensive(Game *g, int *row, int *col){
    char move[100];
    printf("Press enter for computer move (0 for main menu): ");
    input_str(move, sizeof(move));
    if (move[0] == '0') {
        return false;
    }
    //evaluate the board for the opponent
    char sign = g->actual_player == 0 ? g->p2sign : g->p1sign;
    evaluate_board(g, row, col, sign);
    return true;
}

bool computer_move_random(Game *g, int *row, int *col){
    char move[100];
    bool valid = false;
    printf("Press enter for computer move (0 for main menu): ");
    input_str(move, sizeof(move));
    if (move[0] == '0') {
        return false;
    }
    if (is_board_empty(g)){
        *row = g->boardsize / 2;
        *col = g->boardsize / 2;
    }
    else {
        while (!valid){
            *row = rand() % g->boardsize;
            *col = rand() % g->boardsize;
            if (g->board[*row][*col] == ' '){
                if (has_neighbour(g, *row, *col)){
                    valid = true;
                }
            }
        }
    }
    return true;
}

bool mark_player_move(Game *g, int row, int col){
    char sign = g->actual_player == 0 ? g->p1sign : g->p2sign;
    if (g->board[row][col] != ' '){
        printf("Invalid move!\n");
        return false;
    }
    g->board[row][col] = sign;
    return true;
}
