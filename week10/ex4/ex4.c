#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

typedef struct Entry {
    char* fileName;
    char** hardlink;
} entry_t;

int getHardlinkCount(entry_t* entry) {
    int count = 0;
    while (entry->hardlink[count] != NULL) {
        count++;
    }
    return count;
}

int 
main(int argc, char *argv[]) {
    entry_t* entries = calloc(255, sizeof(entry_t));
    DIR *dir;
    struct dirent *ent;
    char* path = "/home/halcyon/study/OS/OS/week10/ex4/tmp";
    if ((dir = opendir(path)) != NULL) {
        int i = 0;
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG) {
                entries[i].fileName = ent->d_name;
                entries[i].hardlink = calloc(255, sizeof(char*));
                int j = 0;
                DIR *dir2;
                struct dirent *ent2;
                if ((dir2 = opendir(path)) != NULL) {
                    while ((ent2 = readdir(dir2)) != NULL) {
                        if (ent2->d_type == DT_REG) {
                            if (ent->d_ino == ent2->d_ino) {
                                entries[i].hardlink[j] = ent2->d_name;
                                j++;
                            }
                        }
                    }
                    printf("​");
                    closedir (dir2);
                } else {
                    return EXIT_FAILURE;
                }
                i++;
            }
        }
        closedir (dir);
    } else {
        return EXIT_FAILURE;
    }
    for (int i = 0; i < 255; i++) {
        if (entries[i].fileName != NULL) {
            int count = 0;
            for (int j = 0; j < 255; j++) {
                if (entries[i].hardlink[j] != NULL) {
                    count++;
                }
            }
            if (count > 1) {
                printf("%s: ", entries[i].fileName);
                for (int j = 0; j < 255; j++) {
                    if ((entries[i].hardlink[j] != NULL) && (count > 1)) {
                        printf("%s ", entries[i].hardlink[j]);
                    }
                }
                printf("\n");
            }
        }
    }
    return EXIT_SUCCESS;
}