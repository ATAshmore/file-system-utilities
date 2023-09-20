//  myls-Alexander.c
//  list files

/*
Write a program that lists files in the given directory.When called without any
arguments, the program should just print the file names. When invoked with the -l flag, the
program should print out information about each file, such as the owner, group,
permissions, and other information obtained from the stat() system call. The program
should take one additional argument, which is the directory to read, e.g., myls -l directory.
If no directory is given, the program should just use the current working directory.

Useful interfaces: stat(), opendir(), readdir(), getcwd()
*/

#include "Directory.h"


/*  list files in a given direcotry. if no arguements, prints only file names
    if -l print information for owner, group, permissions, others.
    getpwuid used for usernameID
    getgrdig used for group name associated with group ID*/
void listFiles(char* directory, int showDetails) {
    DIR* dir;               //directory
    Dir* file;              //file
    DirInfo fileInfo;       //file info
    char* fileName;         //filename
    char perm_string[11];   //permission string
    struct passwd *pwd;     //struct for username
    struct group *grp;      //struct for groupname

    // Open the directory
    if ((dir = opendir(directory)) == NULL) {
        printf("opendir error");
        return;
    }

    // read directory: will either print file name or its details:
    // details: permissions, links#, username, groupname, size in bytes,inode, last modification
    while ((file = readdir(dir)) != NULL) {
        // gets full path of file
        fileName = getFolderName(directory, file->d_name);
        // Get file information. check that there isn't issue
        if (stat(fileName, &fileInfo) == -1) {
            printf("stat error");
            return;
        }
        
        // Print file details if showDetails flag is set
        if (showDetails) {
            filemode_to_string(fileInfo.st_mode, perm_string);
            printf("Permission: %s   Links: %ld  ", perm_string, fileInfo.st_nlink);
            pwd = getpwuid(fileInfo.st_uid);
            printf("User: %s  ", pwd->pw_name);
            grp = getgrgid(fileInfo.st_gid);
            printf("Group: %s  ", grp->gr_name);
            printf("Size: %ld\t", fileInfo.st_size);
            printf("Inode: %lu\t", fileInfo.st_ino);
            printTime(&fileInfo.st_mtime);
        }
        // print file's name
        printf("%s\n", file->d_name);
        // free fileName mem
        free(fileName);
    }
    // close directory
    closedir(dir);
}


int main(int argc, char** argv) {
    // set the default values
    char* directory = ".";
    int showFileDetails = 0;
    // parse command line arguments
    if (argc > 1) {
        if (equals(argv[1], "-l")) {
            // set showFileDetails flag if -l is given
            showFileDetails = 1;
            if (argc > 2) {
                // Use the given directory if specified
                directory = argv[2];
            }
        } else {
            // use the first argument as the directory if no flag is given
            directory = argv[1];
        }
    }
    // list files in directory
    listFiles(directory, showFileDetails);
    return 0;
}
