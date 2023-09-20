//  mytail-Alexander.c
//  tail


/*
Write a program that prints out the last few lines of a file. The program should be
efficient, in that it seeks to near the end of the file, reads in a block of data, and then goes
back until it finds the requested number of lines; at this point, it should print out those lines
from the beginning to the end of the file. To invoke the program, one should type: mytail
-n file, where n is the number of lines at the end of the file to print.

Useful interfaces: stat(), lseek(), open(), read(), close(). 
*/

// takes arguements in form of ./myyail -n fileName
// n is number of lines: don't do more than 10. it stops working after reaches buffer size.
// fileName is file name

#include "Directory.h"\

// set buffer size: 1024 bytes
#define BUFFER_SIZE 1024    //  holds the string of text/lines

int main(int argc, char* argv[]) {

    // check if the correct number of arguments have been passed
    if (argc != 3) {
        printf("Wrong number of arguments/use: ./mytail -n filename\n");
        return 1;
    }

    // convert second argument to integer
    int n = atoi(argv[1]);
    // check if number of lines is negative
    if (n < 0) {
        printf("Error: Invalid number of lines\n");
        return 1;
    }

    // store file's name
    char* fileName = argv[2];
    // open file for reading
    int fd = open(fileName, O_RDONLY);

    // check if file opened successfully
    if (fd == -1) {
        printf("Error: Cannot open file\n");
        return 1;
    }

    // get file info
    DirInfo dirInfo = getDirInfo(fileName);
    int fileSize = dirInfo.st_size;

    // set buffer size based on minimum of file size and buffer size
    int buffSize = BUFFER_SIZE < fileSize ? BUFFER_SIZE : fileSize;
    char buffer[buffSize];

    // move file pointer to end of file minus buffer size
    lseek(fd, -buffSize, SEEK_END);

    // read buffer size bytes into buffer
    int bytesRead = read(fd, buffer, buffSize);
    int numLines = 0;

    // loop backwards through buffer
    for (int i = bytesRead - 1; i >= 0; i--) {
        // check for newline character
        if (buffer[i] == '\n' && ++numLines == n) {

            // Found the last n lines
            // create output string of length bytesRead - i
            char* output = newString(bytesRead - i);

            // copy bytesRead - i - 1 bytes from buffer starting at i + 1 into output
            strncpy(output, buffer + i + 1, bytesRead - i - 1);

            // print output
            printf("\n");
            printf("Below are the last %d lines of %s:\n%s", n, fileName, output);

            // free dynamically allocated memory
            free(output);
            printf("\n");
            break;
        }
        // check if we've reached the beginning of the buffer
        else if (i == 0) {
            // handles case when the number of lines in file matches number of lines requested.
            // create output string of length bytesRead
            char* output = newString(bytesRead);

            // copy bytes_read bytes from buffer into output
            strncpy(output, buffer, bytesRead);

            // print output
            printf("\n");
            printf("Below is the entire file %s:\n%s", fileName, output);

            // free dynamically allocated memory
            free(output);
            printf("\n");
        }
    }
    // close file
    close(fd);
    return 0;
}