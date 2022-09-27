#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool
contains(char* str, char ch) {
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == ch)
            return true;
    }
    return false;
}

int
main(void) {
    char cmd_path[256] = "/usr/bin/";
    char* args[256] = {};

    char* cmd = malloc(sizeof(char*));
    printf("Enter the command: ");    
    scanf("%[^\n]", cmd);

    int16_t j = 0;
    if (contains(cmd, ' ')) {
        char* token = strtok(cmd, " ");
        strcat(cmd_path, token);
        while (token != NULL) {
            args[j++] = token;
            token = strtok(NULL, " ");
        }
    } else strcat(cmd_path, cmd);
    
    if (execvp(cmd_path, args) == -1)
        perror("couldn't compile");
}