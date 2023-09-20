# file-system-utilities

This project consists of four different programs based on various UNIX utilities. Each program performs a specific file system-related task. The project is structured in a way that allows easy compilation using a provided makefile.

## Utilities Included

### 1. `mytail`

This utility prints out the last few lines of a file efficiently. It seeks to near the end of the file, reads a block of data, and then goes back until it finds the requested number of lines. To use it, type:

```
./mytail -n file
```

Where `n` is the number of lines to print, and `file` is the name of the file.

### 2. `mystat`

This utility mimics the `stat` command. It calls the `stat()` system call on a given file or directory and prints out information such as file size, number of blocks allocated, reference (link) count, file permissions, and file inode. To use it, simply provide the file or directory as an argument:

```
./mystat filename
```

### 3. `mysearch`

This program recursively searches the file system tree, starting at a given point, and prints out the names of each file and directory encountered. You can specify the starting point by providing a directory as an argument. If no argument is given, it starts from the current working directory.

```
./mysearch [pathName]
```

### 4. `myls`

This utility lists files in a given directory. When invoked without any arguments, it prints only the file names. When used with the `-l` flag, it displays additional details, such as permissions, links, owner, group, size, inode, and modification time. You can specify the directory to list, or it will use the current working directory by default.

```
./myls [-l] [directory]
```

## Building and Running

To compile the utilities, you can use the provided makefile:

```shell
make
```

