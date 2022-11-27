#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "base.h"
#include "debugmalloc.h"

#define SAVE_GAME "amobasave.dat"

// destroys board
void destroy_board(Game *g){
    if (g->board == NULL){
        return;
    }
    for (int i = 0; i < g->boardsize; i++){
        if (g->board[i] != NULL){
            free(g->board[i]);
            g->board[i] = NULL;
        }
    }
    free(g->board);
    g->board = NULL;
}

// creates a new empty board
bool create_board(Game *g){
    if (g->board != NULL){
        return false;
    }
    g->board = (char**) malloc(g->boardsize * sizeof(char*));
    if (g->board == NULL){
        destroy_board(g);
        return false;
    }
    memset(g->board, MARK_EMPTY, g->boardsize * sizeof(char));
    for (int i = 0; i < g->boardsize; i++){
        g->board[i] = (char*) malloc(g->boardsize * sizeof(char));
        if (g->board == NULL){
            destroy_board(g);
            return false;
        }
        memset(g->board[i], MARK_EMPTY, g->boardsize * sizeof(char));
    }
    return true;
}

// saves game
bool save_game(Game *g){
    if (g->board == NULL){
        printf("There is no ongoing game to save!\n");
        return false;
    }
    FILE *fp;
    fp = fopen(SAVE_GAME, "w");
    if (fp == NULL){
        printf("Unable to create file %s!\n", SAVE_GAME);
        return false;
    }
    size_t written = fwrite(g, sizeof(Game) - sizeof(g->board), 1, fp);
    if (written != 1){
        printf("Unable to write save game data!\n");
        fclose(fp);
        return false;
    }
    for (int i = 0; i < g->boardsize; i++){
        written = fwrite(g->board[i], 1, g->boardsize, fp);
        if (written != g->boardsize){
            printf("Unable to write save game data!\n");
            fclose(fp);
            return false;
        }
    }
    fclose(fp);
    return true;
}

// loads game
bool load_game(Game *g){
    FILE *fp;
    destroy_board(g);
    fp = fopen(SAVE_GAME, "r");
    if (fp == NULL){
        printf("Unable to load file %s!\n", SAVE_GAME);
        return false;
    }
    size_t read = fread(g, sizeof(Game) - sizeof(g->board), 1, fp);
    if (read != 1){
        printf("Unable to load save game data!\n");
        fclose(fp);
        return false;
    }
    if (!create_board(g)){
        printf("Not enough memory for creating the board!\n");
        fclose(fp);
        return false;
    }
    for (int i = 0; i < g->boardsize; i++) {
        read = fread(g->board[i], 1, g->boardsize, fp);
        if (read != g->boardsize){
            printf("Unable to load save game data!\n");
            fclose(fp);
            return false;
        }
    }
    fclose(fp);
    return true;
}

// gets a new board size
void board_size(Game *g){
    bool valid = false;
    while (!valid) {
        printf("Enter the size of the board: ");
        input_int(&g->boardsize);
        if (g->boardsize < 5 || g->boardsize > 50){
            printf("Invalid size!\n");
        }
        else {
            valid = true;
        }
    }
    destroy_board(g);
}

// returns the string representation of the row index
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

// decides whether the board is full or not
bool is_board_full(Game *g){
    for (int i = 0; i < g->boardsize; i++){
        for (int j = 0; j < g->boardsize; j++) {
            if (g->board[i][j] == MARK_EMPTY) {
                return false;
            }
        }
    }
    return true;
}

// decides whether the board is empty or not
bool is_board_empty(Game *g){
    for (int i = 0; i < g->boardsize; i++){
        for (int j = 0; j < g->boardsize; j++){
            if (g->board[i][j] != MARK_EMPTY){
                return false;
            }
        }
    }
    return true;
}

// decides whether a cell has any neighbour or not
bool has_neighbour(Game *g, int row, int col){
    for (int i = row - 1; i <= row + 1; i++){
        for (int j = col - 1; j <= col + 1; j++){
            if (i < 0 || i >= g->boardsize || j < 0 || j >= g->boardsize) {
                continue;
            }
            if (i == row && j == col) {
                continue;
            }
            if (g->board[i][j] != MARK_EMPTY){
                return true;
            }
        }
    }
    return false;
}

// evaluate the score of the given position, using different metrics
static int evaluate(Game *g, int row, int col, bool longest_line_mode){
    int maxcount = 0;
    int countsum = 0;
    int count = 1;
    char mark = g->board[row][col];
    if (mark == MARK_EMPTY){
        return 0;
    }

    if (!longest_line_mode && !has_neighbour(g, row, col)){
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
    countsum += count;
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
    countsum += count;
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
    countsum += count;
    count = 1;
    for (k = 1; row - k >= 0 && col + k < g->boardsize; k++){
        if (g->board[row - k][col + k] != mark){
            break;
        }
    }
    count = count + k - 1;
    for (k = 1; row + k < g->boardsize && col - k >= 0; k++){
        if (g->board[row + k][col - k] != mark){
            break;
        }
    }
    count = count + k - 1;
    if (count > maxcount){
        maxcount = count;
    }
    countsum += count;
    if (longest_line_mode){
        return maxcount;
    }
    else {
        return maxcount * 100 + countsum;
    }
}

// length of the longest consecutive line at the given position
static int longest_line(Game *g, int row, int col) {
    return evaluate(g, row, col, true);
}

// evaluate how "good" the move is at the specified position
static int evaluate_move(Game *g, int row, int col) {
    return evaluate(g, row, col, false);
}

// find the next possible move, that has the highest evaluation score
void evaluate_board(Game *g, int *row, int *col, char sign){
    int max = 0;
    int score = 0;
    int maxscore = 0;
    if (is_board_empty(g)){
        *row = g->boardsize / 2;
        *col = g->boardsize / 2;
    }
    else{
        for (int i = 0; i < g->boardsize; i++) {
            for (int j = 0; j < g->boardsize; j++) {
                if (g->board[i][j] == MARK_EMPTY) {
                    g->board[i][j] = sign;
                    score = evaluate_move(g, i, j);
                    if (score > maxscore){
                        maxscore = score;
                        *row = i;
                        *col = j;
                    }
                    g->board[i][j] = MARK_EMPTY;
                }
            }
        }
    }
}

// decides whether any player has won
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

// prints the board, marking the winning line (if any)
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
