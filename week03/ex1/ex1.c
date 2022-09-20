#include <stdlib.h>
#include <stdio.h>

int32_t
main(int argc, char const *argv[]) {
    const int32_t x = 10;
    const int32_t* q = &x;

    const int32_t* const p = malloc(5 * sizeof(int32_t));
    memset(p, x, 5);
    printf("d", *p);
    return 0;
}