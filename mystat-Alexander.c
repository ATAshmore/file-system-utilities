//  mystat-Alexander.c
//  stat()

/*
Write your own version of the command line program stat, which simply calls the
stat() system call on a given file or directory.Print out file size, number of blocks allocated,
reference (link) count, file permissions, and file inode. 

Useful interfaces: stat() 

*/

#include "Directory.h"
/*
struct stat {
    dev_t       st_dev;         //  ID of device containing file
    ino_t       st_ino;         //  inode number
    mode_t      st_mode;        //  protection
    nlink_t     st_nlink;       //  number of hard links
    uid_t       st_uid;         //  user ID of owner
    gid_t       st_gid;         //  group ID of owner 
    dev_t       st_rdev;        //  device ID (if special file)
    off_t       st_size;        //  total size, in bytes
    blksize_t   st_blksize;     //  blocksize for filesystem I/O
    blkcnt_t    st_blocks;      //  number of blocks allocated
    time_t      st_atime;       //  time of last access
    time_t      st_mtime;       //  time of last modification
    time_t      st_ctime;       //  time of last status change
}
*/


/*
needs:
file size                   st_size
number of blocks allocated  st_blocks
reference count(link)       st_nlink
file permissions            st_mode
file inode                  st_ino
*/

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error: wrong number of arguments\n");
        return 1;
    }
    char* fileName = argv[1];

    // Get file stats
    DirInfo dirInfo = getDirInfo(fileName);

    // Convert file mode to permission string
    char permission_string[11];
    filemode_to_string(dirInfo.st_mode, permission_string);

    //  does not work even though strmode() is on system. undefined reference
    // #ifdef __USE_MISC
    // printf("strmode() is supported on this system\n");
    // #else
    // printf("strmode() is not supported on this system\n");
    // #endif
    
    //strmode(dirInfo.st_mode, permission_string);

    // Print file stats
    printf("\n");
    printf("File Information of: %s\n", fileName);
    printf("File Size: %d bytes\n", dirInfo.st_size);
    printf("Number of Blocks: %d\n", dirInfo.st_blocks);
    printf("Number of Links: %d\n", dirInfo.st_nlink);
    printf("File Permissions: %s\n", permission_string);
    printf("File Inode: %lu\n", (unsigned long)dirInfo.st_ino); //  needs to be unsigned long or negative number
    printf("\n");
}
