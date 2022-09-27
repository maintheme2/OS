#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>

int 
main() {
	pid_t pid1 = fork();

    clock_t t1 = clock();

    if (pid1 == 0) {
        t1 = clock() - t1;
        printf("child1: %d, parent: %d\nit took me %lfms to finish child1\n",
        getpid(), getppid(), (double)t1 / CLOCKS_PER_SEC * 1000);

    } else {
        pid_t pid2 = fork();
        clock_t t2 = clock();

        if (pid2 == 0) {
            t2 = clock() - t2;
            printf("child2: %d, parent: %d\nit took me %lfms to finish child2\n", 
            getpid(), getppid(), (double)t2 / CLOCKS_PER_SEC * 1000);

        } else {
            t1 = clock() - t1;
            printf("main: %d, parent: %d\nit took me %lfms to finish main\n", 
            getpid(), getppid(), (double)t1 / CLOCKS_PER_SEC * 1000);
        }
    }
	return EXIT_SUCCESS;
}