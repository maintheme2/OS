#include <stdlib.h>
#include <stdio.h>
#include <string.h>

short file_counter;

typedef struct File {
    short id;
    short size; 

    char* name;
    char* data;
    
    struct Directory* parent;
}file_t;

typedef struct Directory {
    file_t* files[256];
    struct Directory* directories[8];
    struct Directory* parent;

    char* name;

    size_t nf;
    size_t nd;
}directory_t;

directory_t*
create_directory(char* name) {
    directory_t* new_directory = malloc(sizeof(directory_t));
    new_directory->name = name;
    new_directory->parent = NULL;
    new_directory->nf = 0;
    new_directory->nd = 0;
    return new_directory;
}

void
add_directory(directory_t* parent, directory_t* new_directory) {
    parent->directories[parent->nd++] = new_directory;
    new_directory->parent = parent;
}

char*
get_directory_path(directory_t* directory) {
    char* path = malloc(2048);
    char* name = directory->name;
    while (directory->parent != NULL) {
        directory = directory->parent;
        strcat(path, directory->name);
        if (strcmp(directory->name, "/") != 0)
            strcat(path, "/");
    }
    strcat(path, name);
    return path;
}

file_t*
create_file(char* name) {
    file_t* new_file = malloc(sizeof(file_t));
    new_file->name = calloc(64, sizeof(char));
    strcpy(new_file->name, name);
    new_file->id = file_counter++;
    new_file->data = NULL;
    new_file->size = 0;
    new_file->parent = NULL;
    return new_file;
}

void 
add_file(file_t* file, directory_t* directory) {
    directory->files[directory->nf++] = file;
    file->id = file_counter++;
    file->parent = directory;
}

void 
add_to_file(file_t* file, const char* str) {
    file->data = calloc(1024, sizeof(char));
    strcpy(file->data, str);
    file->size = strlen(str) + 1;
}

void 
append_to_file(file_t* file, const char* str) {
    strcat(file->data, str);
    file->size += strlen(str) + 1;
}

char*
get_file_path(file_t* file) {
    char* path = calloc(256, sizeof(char));
    strcpy(path, get_directory_path(file->parent));
    strcat(path, "/");
    strcat(path, file->name);
    return path;
}
    
void
pwd_file(file_t* file) {
    printf("%s\n", get_file_path(file));
}

int 
main(int argc, char const *argv[]) {
    directory_t* root = create_directory("/");

    directory_t* home = create_directory("home");
    directory_t* bin = create_directory("bin");

    add_directory(root, home);
    add_directory(root, bin);

    file_t* bash = create_file("bash");
    add_to_file(bash, "Bourne Again Shell!!");
    add_file(bash, bin);

    file_t* ex3_1 = create_file("ex3_1.c");
    add_to_file(ex3_1, "int printf(const char * format, ...);");
    append_to_file(ex3_1, "int main(){printf(”Hello World!”)}");
    add_file(ex3_1, home);

    file_t* ex3_2 = create_file("ex3_2.c");
    add_to_file(ex3_2, "// This is a comment in C language");
    add_file(ex3_2, home);

    // printf("%s\n", ex3_1->data);

    pwd_file(bash);
    pwd_file(ex3_1);
    pwd_file(ex3_2);
    return 0;
}
