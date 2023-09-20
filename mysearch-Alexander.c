//  mysearch-Alexander.c
//  recursive search

/*
Write a program that prints out the names of each file and directory in
the file system tree, starting at a given point in the tree. For example, when run without
arguments, the program should start with the current working directory and print its
contents, as well as the contents of any sub-directories, etc., until the entire tree, root at the
CWD, is printed. If given a single argument (of a directory name), use that as the root of
the tree instead.

Useful interfaces: you figure it out. :(
*/

#include "Directory.h"

// print indent according to how many subdirectory its in
void printTab(int level) {
    for (int i = 0; i < level; i++) {
        printf("   ");
    }
}
//  list contents of ofler recursively
void listFolder(char *pathName, int level) {
    // open directory with pathName
    DIR *rootDir = opendir(pathName);
    Dir* dir;

    if (rootDir == NULL) {
        // If directory couldn't be opened, print error message and exit program
        printf("Error: could not open directory %s\n", pathName);
        exit(1);
    }

    // loop through all directory entries
    while ((dir = readdir(rootDir)) != NULL) {
        // ignore "." and ".." directory entries
        if (equals(dir->d_name, ".") || equals(dir->d_name, "..")) {
            continue;
        }

        // Print the current dir with appropriate indentation
        printTab(level);
        printf("%s\n", dir->d_name);

        // If current dir is a directory, list its contents recursively
        if (dir->d_type == DT_DIR) {
            char* sub_folder_name = getFolderName(pathName, dir->d_name);
            listFolder(sub_folder_name, level + 1);
            free(sub_folder_name);
        }
    }
    // Close directory
    closedir(rootDir);
}

int main(int argc, char **argv) {
    char *pathName;
    if (argc == 1) {
        // if no arguments provided, use current working directory
        pathName = ".";
    } else if (argc == 2) {
        // if one argument provided, use provided path
        pathName = argv[1];
    } else {
        // if more than one argument provided, print usage message and exit program
        printf("usage: %s [pathName]\n", argv[0]);
        return 0;
    }
    // print starting message then  list folder contents recursively
    printf("Starting at: %s\n", pathName);
    listFolder(pathName, 0);
    printf("Search has finished!\n");

    return 0;
}