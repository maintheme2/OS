#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void
print_ascending(int n) {
    for (size_t i = 1; i <= n; i++) {
        for (size_t j = 0; j < i; j++)
            printf("*");
        printf("\n");
    }
}

void
print_half(int n) {
    for (size_t i = 0; i < n / 2 + 1; i++) {
        for (size_t j = 0; j <= i; j++)
            printf("*");
        printf("\n");
    }
    for (size_t i = n / 2 ; i > 0; i--) {
        for (size_t j = i; j > 0; j--)
            printf("*");
        printf("\n");
    }
}

void
print_constant(int n) {
    for (size_t i = 1; i <= n; i++) {
        for (size_t j = 0; j < n; j++)
            printf("*");
        printf("\n");
    }
}

int 
main(int argc, char const *argv[]) {
    int n;
    scanf("%i", &n);

    print_ascending(n);
    printf("\n");
    print_half(n);
    printf("\n");
    print_constant(n);

    return 0;
}
