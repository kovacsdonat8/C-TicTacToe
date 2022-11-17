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
        if (g->boardsize < 5 || g->boardsize > 50){
            printf("Invalid size!\n");
        }
        valid = true;
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

int longest_line(Game *g, int row, int col){
    int maxcount = 0;
    int count = 1;
    char mark = get_mark(g, row, col);
    if (mark == ' '){
        return 0;
    }
    int k;
    for (k = 1; col + k < g->boardsize; k++){
        if (get_mark(g, row, col + k) != mark){
            break;
        }
    }
    count = count + k - 1;
    for (k = 1; col - k >= 0; k++){
        if (get_mark(g, row, col - k) != mark){
            break;
        }
    }
    count = count + k - 1;
    if (count > maxcount){
        maxcount = count;
    }
    count = 1;
    for (k = 1; row + k < g->boardsize; k++){
        if (get_mark(g, row + k, col) != mark){
            break;
        }
    }
    count = count + k - 1;
    for (k = 1; row - k >= 0; k++){
        if (get_mark(g, row - k, col) != mark){
            break;
        }
    }
    count = count + k - 1;
    if (count > maxcount){
        maxcount = count;
    }
    count = 1;
    for (k = 1; row + k < g->boardsize && col + k < g->boardsize; k++){
        if (get_mark(g, row + k, col + k) != mark){
            break;
        }
    }
    count = count + k - 1;
    for (k = 1; row - k >= 0 && col - k >= 0; k++){
        if (get_mark(g, row - k, col - k) != mark){
            break;
        }
    }
    count = count + k - 1;
    if (count > maxcount){
        maxcount = count;
    }
    count = 1;
    for (k = 1; row - k >= 0 && col + k < g->boardsize; k++){
        if (get_mark(g, row - k, col + k) != mark){
            break;
        }
    }
    count = count + k - 1;
    for (k = 1; row + k < g->boardsize && col - k > 0; k++){
        if (get_mark(g, row + k, col - k) != mark){
            break;
        }
    }
    count = count + k - 1;
    if (count > maxcount){
        maxcount = count;
    }
    return maxcount;
}

bool is_game_won(Game *g){
    for (int i = 0; i < g->boardsize; i++){
        for (int j = 0; j < g->boardsize; j++){
            if (longest_line(g, i, j) >= 5){
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
            if (longest_line(g, i, j) >= 5){
                printf("|(%c)", get_mark(g, i, j));
            }
            else{
                printf("| %c ", get_mark(g, i, j));
            }
        }
        printf("|\n");
    }
    printf("  -|");
    for (j = 0; j < n; j++){
        printf("---|");
    }
    printf("-\n");
}
