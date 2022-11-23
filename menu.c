#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "base.h"
#include "board.h"
#include "moves.h"

bool ask_yes_or_no(char *question){
    printf("%s (Y/N) ", question);
    char yesno[5];
    input_str(yesno, sizeof (yesno));
    if (yesno[0] == 'Y' || yesno[0] == 'y'){
        return true;
    }
    return false;
}

void set_player_name(char *name){
    input_str(name, NAME_LEN + 1);
}

char *get_player_type_name(int type){
    switch (type) {
        case PLAYER_HUMAN:
            return "Human";
        case PLAYER_CPU_OFFENSIVE:
            return "Computer Offensive";
        case PLAYER_CPU_DEFENSIVE:
            return "Computer Defensive";
        case PLAYER_CPU_RANDOM:
            return "Computer Random";
        default:
            return "Invalid player type!";
    }
}

void set_player_type(int player_number, int *type){
    bool valid = false;
    while (!valid) {
        printf("Enter the type of Player %d "
               "(%d: %s, %d: %s, %d: %s, %d %s): ",
               player_number,
               PLAYER_HUMAN,         get_player_type_name(PLAYER_HUMAN),
               PLAYER_CPU_OFFENSIVE, get_player_type_name(PLAYER_CPU_OFFENSIVE),
               PLAYER_CPU_DEFENSIVE, get_player_type_name(PLAYER_CPU_DEFENSIVE),
               PLAYER_CPU_RANDOM,    get_player_type_name(PLAYER_CPU_RANDOM));
        input_int(type);
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
    bool gameover = false;
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
                        gameover = true;
                    }
                    if (is_board_full(g)){
                        playing = false;
                        print_board(g);
                        printf("\nGAME OVER!\nNo more moves!\nDRAW!\n");
                        gameover = true;
                    }
                    g->actual_player = 1 - g->actual_player;
                }
            }
        } while (!valid);
    }
    if (gameover){
        destroy_board(g);
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
        input_int(&menu);
        switch (menu){
            case 1:
                if (g->board != NULL){
                    if (ask_yes_or_no("There is an ongoing game. Are you sure you want to restart?")){
                        destroy_board(g);
                    }
                }
                if (g->board == NULL) {
                    create_board(g);
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
                write_game(g);
                break;
            case 4:
                if (ask_yes_or_no("Do you want to load game?")){
                    read_game(g);
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
        printf("3. Player 1 Type: %s\n", get_player_type_name(g->p1type));
        printf("4. Player 2 Name: %s\n", g->p2name);
        printf("5. Player 2 Type: %s\n", get_player_type_name(g->p2type));
        printf("0. Main Menu\n");
        input_int(&menu);
        switch (menu){
            case 1:
                board_size(g);
                break;
            case 2:
                printf("Enter the name of Player 1 (max. %d chars): ", NAME_LEN);
                set_player_name(g->p1name);
                break;
            case 3:
                set_player_type(1, &g->p1type);
                break;
            case 4:
                printf("Enter the name of Player 2 (max. %d chars): ", NAME_LEN);
                set_player_name(g->p2name);
                break;
            case 5:
                set_player_type(2, &g->p2type);
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
        input_int(&menu);
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
    g->p2type = PLAYER_CPU_OFFENSIVE;
    g->board = NULL;
    g->actual_player = 0;
}

void exit_game(Game *g){
    destroy_board(g);
}

