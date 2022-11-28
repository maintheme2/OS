#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

int 
main(int argc, char *argv[]) {
    struct input_event ev;
    int size = sizeof(struct input_event);

    int fd = open("/dev/input/by-path/platform-i8042-serio-0-event-kbd", O_RDONLY);
    if (fd == -1) {
        printf("Cannot open device\n");
        exit(1);
    }

    FILE *fp = fopen("ex2.txt", "w");

    int rd;
    while (rd = read(fd, &ev, size)) {
        if (rd < size) {
            printf("Error reading\n");
            exit(1);
        }

        if (ev.type == EV_KEY) {
            if (ev.value == 1) {
                // stop reading when esc is pressed 
                if (ev.code == 1) {
                    break;
                }
                printf("PRESSED: %x (%d)\n", ev.code, ev.code);
                fprintf(fp, "PRESSED: %x (%d)\n", ev.code, ev.code);
            }
            else if (ev.value == 0) {
                printf("RELEASED: %x (%d)\n", ev.code, ev.code);
                fprintf(fp, "RELEASED: %x (%d)\n", ev.code, ev.code);
            }
        }
    }

    fclose(fp);
    close(fd);
    return 0;
}
