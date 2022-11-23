#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void input_str(char *str, int size){
    fgets(str, size, stdin);
    if (str[strlen(str) - 1] == '\n'){
        str[strlen(str) - 1] = '\0';
    }
}

void input_int(int *number){
    char str[50];
    fgets(str, sizeof(str), stdin);
    if (str[strlen(str) - 1] == '\n'){
        str[strlen(str) - 1] = '\0';
    }
    *number = atoi(str);
}