//  Directory.h
//  provided by lecture

#include <unistd.h>

#include <pwd.h>
#include <grp.h>

#include <fcntl.h>
//https://pubs.opengroup.org/onlinepubs/007904975/basedefs/fcntl.h.html

#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>


typedef struct dirent Dir;
typedef struct stat DirInfo;
typedef struct tm TimeInfo;

//void strmode(mode_t mode, char *buf);

char* newString(int length){
    return (char*)malloc(length*sizeof(char));
}

int equals(char* string1, char* string2){
    return strcmp(string1, string2)==0?1:0;
}

DirInfo getDirInfo(char* dir){
    DirInfo dirInfo;
    stat(dir, &dirInfo);
    return dirInfo;
}

void printTime(time_t* time){
    int stringLength=20; char string[stringLength];
    TimeInfo* timeInfo=(TimeInfo*)localtime(time);
    strftime(string, stringLength, "%b %d %H:%M",
    timeInfo); printf("Time: %s\t", string);
}

// Convert file mode to permission string
//use bitwise-AND and bit-shift operators to find corresponding 
//char cause this stupid ass strmode() wont work
// used this for reference: https://www.gnu.org/software/libc/manual/html_node/Permission-Bits.html
void filemode_to_string(mode_t mode, char *str) {
    // user permissions
    str[0] = S_ISREG(mode)? '-': S_ISDIR(mode)? 'd': S_ISLNK(mode)?'l' : '?';   //  set file type
    str[1] = (mode & S_IRUSR)? 'r': '-';
    str[2] = (mode & S_IWUSR)? 'w': '-';
    //  group permissions
    str[3] = (mode & S_IXUSR)? 'x': '-';
    str[4] = (mode & S_IRGRP)? 'r': '-';
    str[5] = (mode & S_IWGRP)? 'w': '-';
    // other permissions
    str[6] = (mode & S_IXGRP)? 'x': '-';
    str[7] = (mode & S_IROTH)? 'r': '-';
    str[8] = (mode & S_IWOTH)? 'w': '-';
    str[9] = (mode & S_IXOTH)? 'x': '-';
    //  end of string
    str[10] = '\0';
}

//  provided by lecture
char* getFolderName(char* parentFolder, char* childFolder){
    char* name = newString(strlen(parentFolder)+1+strlen(childFolder)); /* parentFolder+"/"+childFolder */
    sprintf(name, "%s/%s", parentFolder, childFolder);
    return name;
}
