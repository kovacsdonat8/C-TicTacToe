#ifndef AMOBA_NHF_BASE_H
#define AMOBA_NHF_BASE_H

#define NAME_LEN 50
typedef struct Game{
    char p1name[NAME_LEN + 1];
    char p1sign;
    int p1type;
    char p2name[NAME_LEN + 1];
    char p2sign;
    int p2type;
    int boardsize;
    char *board;
    int actual_player;
}Game;

#endif //AMOBA_NHF_BASE_H
