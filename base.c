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
    char str[50];
    input_str(str, sizeof(str));
    *number = atoi(str);
}