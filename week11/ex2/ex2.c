#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int 
main(int argc, char *argv[]) {
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir ("/")) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            printf ("%s\n", ent->d_name);
        }
        closedir (dir);
    } else {
        /* could not open directory */
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}