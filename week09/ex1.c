#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Page {
    int number;
    int counter;
} page_t;

int 
main(int argc, char *argv[]) {
    int page_hits, page_faults;
    if (argc <= 1) {
        fprintf(stderr,
                "Enter the number of page frames\n");
        exit(1);
    }

    int page_frames = atoi(argv[1]);

    FILE *input = fopen("input.txt", "r");

    if (input == NULL) {
        fprintf(stderr, "Can't open file.\n");
        exit(1);
    }

    page_t* processes = calloc(page_frames, sizeof(page_t));
    int num;
    while (fscanf(input, "%d", &num) != EOF) {
        bool found = false;
        printf("\n");
        for (int i = 0; i != page_frames; i++) {
            if (processes[i].number == num) {
                page_hits++;
                found = true;
                break;
            }
        }
        if (!found) {
            page_faults++;
            unsigned int min = 9999999;
            int min_index = 0;
            for (int i = 0; i < page_frames; i++) {
                if (processes[i].counter < min) {
                    min = processes[i].counter;
                    min_index = i;
                }
            }
            processes[min_index].number = num;
        }

        for (int i = 0; i < page_frames; i++) {
            processes[i].counter >>= 1;
            if (processes[i].number == num) {
                processes[i].counter |= 1 << sizeof(int) * 8 - 1;
            }
        }
        printf("NUM: %d\n", num);
        for (int i = 0; i < page_frames; i++) {
            printf("%d ", processes[i].number);
        }

    }
    fclose(input);

    printf("Page hits: %d, page faults: %d\n", page_hits, page_faults);

    printf("Ratio: %f", (float)page_hits / page_faults);

    free(processes);
    return 0;
}
