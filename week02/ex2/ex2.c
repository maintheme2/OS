#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool
contains(char symb, char* str) {
    for (size_t i = 0; i < strlen(str); i++) {
        if (str[i] == symb)
            return true;
    }
    return false;
}

int
main() {
    char* str = malloc(sizeof(char*));
    fgets(str, 256, stdin);
    char* reversed = malloc(sizeof(char*));

    if (contains('.', str)) {
        for (size_t i = 0; i < strlen(str); i++) {
            if (str[i] == '.') break;
            else reversed[i] = str[i];
        }
    }
    else strcpy(reversed, str);
    
    size_t len = strlen(reversed);
    for (size_t j = 0; j < len/2; j++) {
        char temp = reversed[j];
        reversed[j] = reversed[len - j - 1];
        reversed[len - j - 1] = temp;
    }

    printf("\"%s\"", reversed);
    free(str);
    free(reversed);
}