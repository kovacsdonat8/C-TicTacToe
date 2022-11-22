#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "base.h"

#define SAVE_GAME "amobasave.txt"

bool create_board(Game *g){
    g->board = (char**) malloc(g->boardsize * sizeof(char*));
    for (int i = 0; i < g->boardsize; i++){
        g->board[i] = (char*) malloc(g->boardsize * sizeof(char));
        memset(g->board[i], ' ', g->boardsize * sizeof(char));
    }
    return true;
}

void destroy_board(Game *g){
    if (g->board == NULL){
        return;
    }
    for (int i = 0; i < g->boardsize; i++){
        free(g->board[i]);
    }
    free(g->board);
    g->board = NULL;
}

bool write_game(Game *g){
    FILE *fp;
    fp = fopen(SAVE_GAME, "w");
    fwrite(g, sizeof(Game) - sizeof(char *), 1, fp);
    for (int i = 0; i < g->boardsize; i++){
        fwrite(g->board[i], 1, g->boardsize, fp);
    }
    fclose(fp);
    return true;
}

bool read_game(Game *g){
    FILE *fp;
    destroy_board(g);
    fp = fopen(SAVE_GAME, "r");
    fread(g, sizeof(Game) - sizeof(char *), 1, fp);
    create_board(g);
    for (int i = 0; i < g->boardsize; i++) {
        fread(g->board[i], 1, g->boardsize, fp);
    }
    fclose(fp);
    return true;
}

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
    for (int i = 0; i < g->boardsize; i++){
        for (int j = 0; j < g->boardsize; j++) {
            if (g->board[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

bool is_board_empty(Game *g){
    for (int i = 0; i < g->boardsize; i++){
        for (int j = 0; j < g->boardsize; j++){
            if (g->board[i][j] != ' '){
                return false;
            }
        }
    }
    return true;
}

bool has_neighbour(Game *g, int row, int col){
    for (int i = row - 1; i <= row + 1; i++){
        for (int j = col - 1; j <= col + 1; j++){
            if (i < 0 || i >= g->boardsize || j < 0 || j >= g->boardsize) {
                continue;
            }
            if (i == row && j == col) {
                continue;
            }
            if (g->board[i][j] != ' '){
                return true;
            }
        }
    }
    return false;
}

int longest_line(Game *g, int row, int col){
    int maxcount = 0;
    int count = 1;
    char mark = g->board[row][col];
    if (mark == ' '){
        return 0;
    }
    int k;
    for (k = 1; col + k < g->boardsize; k++){
        if (g->board[row][col + k] != mark){
            break;
        }
    }
    count = count + k - 1;
    for (k = 1; col - k >= 0; k++){
        if (g->board[row][col - k] != mark){
            break;
        }
    }
    count = count + k - 1;
    if (count > maxcount){
        maxcount = count;
    }
    count = 1;
    for (k = 1; row + k < g->boardsize; k++){
        if (g->board[row + k][col] != mark){
            break;
        }
    }
    count = count + k - 1;
    for (k = 1; row - k >= 0; k++){
        if (g->board[row - k][col] != mark){
            break;
        }
    }
    count = count + k - 1;
    if (count > maxcount){
        maxcount = count;
    }
    count = 1;
    for (k = 1; row + k < g->boardsize && col + k < g->boardsize; k++){
        if (g->board[row + k][col + k] != mark){
            break;
        }
    }
    count = count + k - 1;
    for (k = 1; row - k >= 0 && col - k >= 0; k++){
        if (g->board[row - k][col - k] != mark){
            break;
        }
    }
    count = count + k - 1;
    if (count > maxcount){
        maxcount = count;
    }
    count = 1;
    for (k = 1; row - k >= 0 && col + k < g->boardsize; k++){
        if (g->board[row - k][col + k] != mark){
            break;
        }
    }
    count = count + k - 1;
    for (k = 1; row + k < g->boardsize && col - k > 0; k++){
        if (g->board[row + k][col - k] != mark){
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
                printf("|(%c)", g->board[i][j]);
            }
            else{
                printf("| %c ", g->board[i][j]);
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
