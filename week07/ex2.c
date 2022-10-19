#include <stdio.h>
#include <stdlib.h>

int 
main() {
    int *array, n;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    array = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; ++i) {
        *(array + i) = i;
    }

    printf("The elements of the array are: ");
    for (int i = 0; i < n; ++i) {
        printf("%d, ", *(array + i));
    }

    free(array);
    return 0;
}