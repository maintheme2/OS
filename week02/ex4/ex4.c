#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void
count(char* str, char symb) {
    int counter = 0;
    for (int i = 0; i < strlen(str); i++) 
        if (str[i] == symb) counter++;

    printf("%c:%d", symb, counter);
}

void
count_all(char* str) {
    for (int i = 0; i < strlen(str) - 1; i++) {
        count(str, str[i]);
        if (i!= (strlen(str) - 2)) printf(", ");
    }
}

int 
main(int argc, char const *argv[]) {
    char* str = malloc(sizeof(char*));
    fgets(str, 256, stdin);

    char symb;
    char* str_to_use = malloc(sizeof(char*));
    for (int i = 0; i < strlen(str); i++) {
        str_to_use[i] = tolower(str[i]);
        if (str[i] == ',') {
            symb = str[i+2];
            break;
        }
    }
    count(str_to_use, symb);
    printf("\n");
    count_all(str_to_use);
    free(str);
    free(str_to_use);
    return 0;
}