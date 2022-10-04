#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int 
main(int argc, char const *argv[]) {
    int fds[2];
    char* to_publish = malloc(1024);

    if (pipe(fds) == -1) {
        perror("Something wrong with piping");
        return 1;
    }

    pid_t pid = fork();
    if (pid != 0) {
        while (fgets(to_publish, sizeof(to_publish), stdin) != NULL) {
            close(fds[0]);
            if (write(fds[1], to_publish, 1024) == -1) {
                perror("Something wrong with writing");
                return 2;
            }
        }
        close(fds[1]);
        wait(NULL);
        } else {
            close(fds[1]);
            while (read(fds[0], to_publish, 1024) != -1) {
                printf("%s", to_publish);
            }
            close(fds[0]);
        }        
    return 0;
}