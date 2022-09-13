#include <stdlib.h>
#include <stdio.h>

void
tribonacci(short n) {
    if ((n < 0) || (n > 37)) {
        printf("cannot calculate");
        return NULL;
    }
    else if (n == 0) {
        printf("%d", 0);
        return NULL;
    }
    // else if ((n == 1) || (n == 2)) {
    //     printf("%d", 1);
    //     return NULL;
    // }
    else {
        size_t prev_prev_prev_num = 0;
        size_t prev_prev_num = 1;
        size_t prev_num = 1;
        size_t current_num = 2;

        for (short i = 3; i < n; i++) {
            prev_prev_prev_num = prev_prev_num;
            prev_prev_num = prev_num;
            prev_num = current_num;
            current_num = prev_prev_prev_num + prev_prev_num + prev_num;
        }
        printf("%ld", current_num);
    }
}

int
main(int argc, char const *argv[]) {
    tribonacci(4);
    printf("\n");
    tribonacci(36);
    return 0;
}
