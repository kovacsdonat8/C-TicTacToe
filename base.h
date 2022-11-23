#ifndef AMOBA_NHF_BASE_H
#define AMOBA_NHF_BASE_H

#define NAME_LEN 50
#define PLAYER_HUMAN 1
#define PLAYER_CPU_OFFENSIVE 2
#define PLAYER_CPU_DEFENSIVE 3
#define PLAYER_CPU_RANDOM 4

typedef struct Game{
    char p1name[NAME_LEN + 1];
    char p1sign;
    int p1type;
    char p2name[NAME_LEN + 1];
    char p2sign;
    int p2type;
    int boardsize;
    int actual_player;
    //this must be the last member
    char **board;
}Game;

// make clion debugger show standard output
#define printf setbuf(stdout,0);printf
#endif //AMOBA_NHF_BASE_H
