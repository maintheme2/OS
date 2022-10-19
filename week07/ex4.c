#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

void 
*my_realloc(void *ptr, size_t size) {
    if (ptr == NULL) {
        return malloc(size);
    }

    if (size == 0) {
        free(ptr);
        return NULL;
    }

    void *new_ptr = malloc(size);
    if (new_ptr == NULL) {
        return NULL;
    }

    size_t min_size = size < malloc_usable_size(ptr) ? size : malloc_usable_size(ptr);
    for (size_t i = 0; i < min_size; i++) {
        *((int *)new_ptr + i) = *((int *)ptr + i);
    }

    free(ptr);
    return new_ptr;
}

int 
main() {
    int *array, n;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    array = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; ++i) {
        *(array + i) = i;
    }

    printf("Old elements of the array are: ");
    for (int i = 0; i < n; ++i) {
        printf("%d, ", *(array + i));
    }

    array = (int *)my_realloc(array, 2 * n * sizeof(int));

    printf("\nNew elements of the array are: ");
    for (int i = 0; i < 2 * n; ++i) {
        printf("%d, ", *(array + i));
    }

    free(array);
    return 0;
}