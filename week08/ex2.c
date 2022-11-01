#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    for (int i = 0; i < 10; i++) {
        void *ptr = malloc(10 * 1024 * 1024);
        memset(ptr, 0, 10 * 1024 * 1024);
        sleep(1);
    }
    return 0;
}

// The si is the pages swapped in from disk to memory.
// The so is the pages swapped out from memory to disk.
// When the program is running the si and so fields are 0.
// When the program is stopped, the si field is 0 and the so field is 1.
// When the program is running again, the si field is 1 and the so field is 0.
// ex3: every second utilized memory increases by 10 MBs
