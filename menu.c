#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "base.h"
#include "board.h"
#include "moves.h"

#define SAVE_GAME "amobasave.txt"

bool ask_yes_or_no(char *question){
    printf("%s (Y/N) ", question);
    char yesno[5];
    scanf("%1s", yesno);
    if (yesno[0] == 'Y' || yesno[0] == 'y'){
        return true;
    }
    return false;
}

void get_player_name(char *name){
    while ((getchar()) != '\n');
    fgets(name, NAME_LEN + 1, stdin);
    if (name[strlen(name) - 1] == '\n'){
        name[strlen(name) - 1] = '\0';
    }
}

void get_player_type(int player_number, int *type){
    bool valid = false;
    while (!valid) {
        printf("Enter the type of Player %d "
               "(%d: Human, %d: Computer Random, %d: Computer Defensive, %d Computer Offensive): ",
               player_number, PLAYER_HUMAN, PLAYER_CPU_RANDOM, PLAYER_CPU_DEFENSIVE, PLAYER_CPU_OFFENSIVE);
        scanf("%d", type);
        if (*type > 0 && *type < 5){
            valid = true;
        }
        else {
            printf("Invalid Player Type!\n");
        }
    }
}

bool next_move(Game *g, int *row, int *col){
    int playertype = g->actual_player == 0? g->p1type : g->p2type;
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

static void play_game(Game *g){
    int menu;
    int row;
    int col;
    bool playing = true;
    bool valid = true;
    while (playing) {
        print_board(g);
        do {
            playing = next_move(g, &row, &col);
            if (playing) {
                valid = mark_player_move(g, row, col);
                if (valid) {
                    if (is_game_won(g)){
                        playing = false;
                        print_board(g);
                        printf("\nGAME OVER!\nThe winner is %s!\n",
                               g->actual_player == 0 ? g->p1name : g->p2name);
                    }
                    if (is_board_full(g)){
                        playing = false;
                        print_board(g);
                        printf("\nGAME OVER!\nNo more moves!\nDRAW!\n");
                    }
                    g->actual_player = 1 - g->actual_player;
                }
            }
        } while (!valid);
    }
}

static void play_menu(Game *g){
    FILE *fp;
    int menu;
    do {
        printf(
                "\n1. New Game\n"
                "2. Continue Game\n"
                "3. Save Game\n"
                "4. Load Game\n"
                "0. Main Menu\n");
        scanf("%d", &menu);
        switch (menu){
            case 1:
                if (g->board != NULL){
                    if (ask_yes_or_no("There is an ongoing game. Are you sure you want to restart?")){
                        free(g->board);
                        g->board = NULL;
                    }
                }
                if (g->board == NULL) {
                    g->board = (char *) malloc(g->boardsize * g->boardsize);
                    memset(g->board, ' ', g->boardsize * g->boardsize);
                    g->actual_player = 0;
                    play_game(g);
                }
                break;
            case 2:
                if (g->board == NULL){
                    printf("There are no ongoing games!\n");
                }
                else{
                    play_game(g);
                }
                break;
            case 3:
                fp = fopen(SAVE_GAME, "w");
                fwrite(g, sizeof(Game) - sizeof(char *), 1, fp);
                fwrite(g->board, 1, g->boardsize * g->boardsize, fp);
                fclose(fp);
                break;
            case 4:
                if (ask_yes_or_no("Do you want to load game?")){
                    fp = fopen(SAVE_GAME, "r");
                    fread(g, sizeof(Game) - sizeof(char *), 1, fp);
                    g->board = (char *) malloc(g->boardsize * g->boardsize);
                    fread(g->board, 1, g->boardsize * g->boardsize, fp);
                    fclose(fp);
                }
                break;
            case 0:
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
    } while (menu != 0);
}

static void options_menu(Game *g){
    int menu;
    do {
        printf("\n1. Size\n");
        printf("2. Player 1 Name: %s\n", g->p1name);
        printf("3. Player 1 Type: %d\n", g->p1type);
        printf("4. Player 2 Name: %s\n", g->p2name);
        printf("5. Player 2 Type: %d\n", g->p2type);
        printf("0. Main Menu\n");
        scanf("%d", &menu);
        switch (menu){
            case 1:
                board_size(g);
                break;
            case 2:
                printf("Enter the name of Player 1 (max. %d chars): ", NAME_LEN);
                get_player_name(g->p1name);
                break;
            case 3:
                get_player_type(1, &g->p1type);
                break;
            case 4:
                printf("Enter the name of Player 2 (max. %d chars): ", NAME_LEN);
                get_player_name(g->p2name);
                break;
            case 5:
                get_player_type(2, &g->p2type);
                break;
            case 0:
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
    } while (menu != 0);
}

static void print_rules(void){
    printf("\nThis game is played by two players on a square grid board.\n");
    printf("Players take turns placing their own marks (\"O\" or \"X\") in one of the still empty squares.\n");
    printf("The game ends if one player wins or if the board is full, in which case it will be a draw outcome.\n");
    printf("To win, one player needs at least 5 marks in a line, each other next to it.\n"); // next to each other either horizontally, vertically or diagonally.
    printf("The line can be horizontal, vertical or diagonal.\n");
}


void main_menu(Game *g){
    int menu;
    do {
        printf(
                "\n1. Play\n"
                "2. Options\n"
                "3. Rules\n"
                "0. Exit\n");
        scanf("%d", &menu);
        switch (menu){
            case 1:
                play_menu(g);
                break;
            case 2:
                options_menu(g);
                break;
            case 3:
                print_rules();
                break;
            case 0:
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
    } while (menu != 0);
}

void init_game(Game *g){
    g->boardsize = 10;
    strcpy(g->p1name, "Player 1");
    g->p1sign = 'X';
    g->p1type = PLAYER_HUMAN;
    strcpy(g->p2name, "Player 2");
    g->p2sign = 'O';
    g->p2type = PLAYER_CPU_RANDOM;
    g->board = NULL;
    g->actual_player = 0;
}

void exit_game(Game *g){
    if (g->board != NULL){
        free(g->board);
        g->board = NULL;
    }
}

