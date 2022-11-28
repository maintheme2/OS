#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <linux/input.h>

_Bool 
checkForExclamation(int* pressed, int pressedSize) {
    if (pressed[2] && pressed[42] && pressedSize == 2) {
        return 1;
    }
    return 0;
}

_Bool 
checkForExam(int* pressed, int pressedSize) {
    if (pressed[25] && pressed[18] && pressedSize == 2) {
        return 1;
    }
    return 0;
}

_Bool 
checkForCap(int* pressed, int pressedSize) {
    if (pressed[30] && pressed[46] && pressed[25] && pressedSize == 3) {
        return 1;
    }
    return 0;
}

int
main(int argc, char *argv[]) {
    printf("Shortcuts:\n");
    printf("LeftShift + 1 = stop reading and terminate programm\n");
    printf("p + e = I passed the Exam!\n");
    printf("c + p + a = Get some cappuccino\n");

    struct input_event ev;
    int size = sizeof(struct input_event);

    int fd = open("/dev/input/by-path/platform-i8042-serio-0-event-kbd", O_RDONLY);
    if (fd == -1) {
        printf("Cannot open device\n");
        exit(1);
    }

    FILE *fp = fopen("ex3.txt", "w");
    int rd;

    int pressed[150] = {0};
    int pressedSize = 0;

    while (rd = read(fd, &ev, size)) {
        if (rd < size) {
            printf("Error reading\n");
            exit(1);
        }

        if (ev.type == EV_KEY) {
            if (ev.value == 0) {
                if (0 <= ev.code && ev.code <= 150 && pressed[ev.code] == 1) {
                    pressed[ev.code] = 0;
                    --pressedSize;
                }

            } else if (ev.value == 1 || ev.value == 2) {
                if (0 <= ev.code && ev.code <= 150 && pressed[ev.code] == 0) {
                    pressed[ev.code] = 1;
                    ++pressedSize;
                }

                // check for exclamation
                if (checkForExclamation(pressed, pressedSize)) {
                    break;
                }
                
                // check for exam
                if (checkForExam(pressed, pressedSize)) {
                    printf("I passed the Exam!\n");
                    fprintf(fp, "I passed the Exam!\n");
                }

                // check for cap
                if (checkForCap(pressed, pressedSize)) {
                    printf("Get some cappuccino\n");
                    fprintf(fp, "Get some cappuccino\n");
                }

            } 
        }
    }

    fclose(fp);
    close(fd);
    return 0;
}

