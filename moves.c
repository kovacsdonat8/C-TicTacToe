#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "base.h"
#include "board.h"

bool computer_move_random(Game *g, int *row, int *col){
    char move[2];
    bool valid = false;
    printf("Press enter for computer move (0 for main menu): ");
    while ((getchar()) != '\n');
    fgets(move, 1, stdin);
    if (move[strlen(move) - 1] == '\n'){
        move[strlen(move) - 1] = '\0';
    }
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
            if (get_mark(g, *row, *col) == ' '){
                if (has_neighbour(g, *row, *col)){
                    valid = true;
                }
            }
        }
    }
    return true;
}

bool computer_move_defensive(Game *g, int *row, int *col){

}

bool computer_move_offensive(Game *g, int *row, int *col){
    char move[2];
    int max = 0;
    printf("Press enter for computer move (0 for main menu): ");
    while ((getchar()) != '\n');
    fgets(move, 1, stdin);
    if (move[strlen(move) - 1] == '\n'){
        move[strlen(move) - 1] = '\0';
    }
    if (move[0] == '0') {
        return false;
    }
    if (is_board_empty(g)){
        *row = g->boardsize / 2;
        *col = g->boardsize / 2;
    }
    else{
        for (int i = 0; i < g->boardsize; i++) {
            for (int j = 0; j < g->boardsize; j++) {
                if (get_mark(g, i, j) == ' ') {
                    set_mark(g, i, j, 0);
                    if (longest_line(g, i, j) > max) {
                        max = longest_line(g, i, j);
                        *row = i;
                        *col = j;
                    }
                    set_mark(g, i, j, 1);
                }
            }

        }
    }
    return true;
}

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

bool mark_player_move(Game *g, int row, int col){
    char sign = g->actual_player == 0 ? g->p1sign : g->p2sign;
    int index = row * g->boardsize + col;
    if (g->board[index] != ' '){
        printf("Invalid move!\n");
        return false;
    }
    g->board[index] = sign;
    return true;
}
