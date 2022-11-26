#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// gets a string input from the user
void input_str(char *str, int size){
    fgets(str, size, stdin);
    if (str[strlen(str) - 1] == '\n'){
        str[strlen(str) - 1] = '\0';
    }
}

// gets a string input from the user and converts into integer
void input_int(int *number){
    //TODO: just call input_str instead of doing the same fgets trickery
    int size = 50;
    char str[size];
    input_str(str, size);
    if (str[strlen(str) - 1] == '\n'){
        str[strlen(str) - 1] = '\0';
    }
    *number = atoi(str);
}