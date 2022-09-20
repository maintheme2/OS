#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

size_t
foo(short age) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    size_t year = tm.tm_year + 1900;
    return year - age;
}

int32_t
main(int argc, char const *argv[]) {
    const int32_t x = 10;
    const int32_t* q = &x;

    int32_t* const p = malloc(5 * sizeof(int32_t));
    
    memset(p, x, 5);
    for (short i = 0; i < 5; i++) 
        printf("%p ", (p+i));

    printf("\n");
    
    for (short i = 0; i < 5; i++) {
        short age;
        scanf("%hd", &age);
        *(p+i) = age;
    }

    for (short i = 0; i < 5; i++) 
        *(p+i) = foo(*(p+i));

    // for (short i = 0; i < 5; i++) 
    //     printf("%d ", *(p+i));

    free(p);
    return 0;
}