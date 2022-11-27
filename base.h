#ifndef AMOBA_NHF_BASE_H
#define AMOBA_NHF_BASE_H

#define NAME_LEN 50

#define PLAYER_HUMAN 1
#define PLAYER_CPU_OFFENSIVE 2
#define PLAYER_CPU_DEFENSIVE 3
#define PLAYER_CPU_RANDOM 4

#define MARK_EMPTY ' '
#define MARK_PLAYER_ONE 'X'
#define MARK_PLAYER_TWO 'O'

typedef struct Player{
    char name[NAME_LEN + 1];
    char sign;
    int type;
}Player;

typedef struct Game{
    Player player[2];
    int actual_player;
    int boardsize;
    // this must be the last member, it is saved separately
    char **board;
}Game;

void input_str(char *str, int size);
void input_int(int *number);

// make clion debugger show standard output
// #define printf setbuf(stdout,0);printf
#endif //AMOBA_NHF_BASE_H
