#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "base.h"
#include "board.h"

// asks a move from the human player and decides whether it's a valid move
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
        if (*row < 0 || *row >= g->boardsize || *col < 0 || *col >= g->boardsize){
            printf("Invalid move!\n");
            continue;
        }
        return true;
    }
}

// this is the algorithm for the offensive computer
bool computer_move_offensive(Game *g, int *row, int *col){
    char move[100];
    printf("Press enter for computer move (0 for main menu): ");
    input_str(move, sizeof(move));
    if (move[0] == '0') {
        return false;
    }
    //evaluate the board for ourselves
    char sign = g->player[g->actual_player].sign;
    evaluate_board(g, row, col, sign);
    return true;
}

// this is the algorithm for the defensive computer
bool computer_move_defensive(Game *g, int *row, int *col){
    char move[100];
    printf("Press enter for computer move (0 for main menu): ");
    input_str(move, sizeof(move));
    if (move[0] == '0') {
        return false;
    }
    //evaluate the board for the opponent
    char sign = g->player[1 - g->actual_player].sign;
    evaluate_board(g, row, col, sign);
    return true;
}

// this is the algorithm for the random computer
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
            if (g->board[*row][*col] == MARK_EMPTY){
                if (has_neighbour(g, *row, *col)){
                    valid = true;
                }
            }
        }
    }
    return true;
}

// sets a mark at the specified row, col of the game board
bool mark_player_move(Game *g, int row, int col){
    char sign =  g->player[g->actual_player].sign;
    if (g->board[row][col] != MARK_EMPTY){
        printf("Invalid move!\n");
        return false;
    }
    g->board[row][col] = sign;
    return true;
}

// processes the next move depending on the player type
bool next_move(Game *g, int *row, int *col){
    int playertype = g->player[g->actual_player].type;
    switch (playertype) {
        case PLAYER_HUMAN:
            return human_move(g, row, col);
        case PLAYER_CPU_RANDOM:
            return computer_move_random(g, row, col);
        case PLAYER_CPU_DEFENSIVE:
            return computer_move_defensive(g, row, col);
        case PLAYER_CPU_OFFENSIVE:
            return computer_move_offensive(g, row, col);
        default:
            printf("Invalid Player Type!\n");
            break;
    }
    return false;
}
