#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "base.h"

char get_mark(Game *g, int row, int col){
    return g->board[row * g->boardsize + col];
}

/*
char set_mark(Game *g, int row, int col){

}
*/

void board_size(Game *g){
    bool valid = false;
    while (!valid) {
        printf("Enter the size of the board: ");
        scanf("%d", &g->boardsize);
        if (g->boardsize >= 5){
            valid = true;
        }
        printf("Invalid move!\n");
    }
    free(g->board);
    g->board = NULL;
}

static void rowname(int index, char *str){
    if (index < 26){
        str[0] = ' ';
        str[1] = 'A' + index;
    }
    else{
        str[0] = 'A';
        str[1] = 'A' + index - 26;
    }
    str[2] = '\0';
}

bool is_board_full(Game *g){
    for (int i = 0; i < g->boardsize * g->boardsize; i++){
        if (g->board[i] == ' '){
            return false;
        }
    }
    return true;
}

bool is_game_won(Game *g){
    for (int i = 0; i < g->boardsize; i++){
        for (int j = 0; j < g->boardsize; j++){
            char mark = get_mark(g, i, j);
            if (mark == ' '){
                continue;
            }
            int k;
            for (k = 1; k < 5 && j + k < g->boardsize; k++){
                if (get_mark(g, i, j + k) != mark){
                    break;
                }
            }
            if (k == 5){
                return true;
            }
            for (k = 1; k < 5 && i + k < g->boardsize; k++){
                if (get_mark(g, i + k, j) != mark){
                    break;
                }
            }
            if (k == 5){
                return true;
            }
            for (k = 1; k < 5 && i + k < g->boardsize && j + k < g->boardsize; k++){
                if (get_mark(g, i + k, j + k) != mark){
                    break;
                }
            }
            if (k == 5){
                return true;
            }
            for (k = 1; k < 5 && i - k >= 0 && j + k < g->boardsize; k++){
                if (get_mark(g, i - k, j + k) != mark){
                    break;
                }
            }
            if (k == 5){
                return true;
            }
        }
    }
    return false;
}

void print_board(Game *g) {
    int n = g->boardsize;
    int i, j;
    char row[3];
    printf("\n  ");
    for (i = 0; i < n; i++){
        printf("  %2d", i + 1);
    }
    printf("\n");
    for (i = 0; i < n; i++){
        printf("  -|", i);
        for (j = 0; j < n; j++){
            printf("---|");
        }
        rowname(i, row);
        printf("-\n%2s ", row);
        for (j = 0; j < n; j++){
            printf("| ");
            printf("%c ", g->board[i * g->boardsize + j]);
        }
        printf("|\n");
    }
    printf("  -|");
    for (j = 0; j < n; j++){
        printf("---|");
    }
    printf("-\n");
}
