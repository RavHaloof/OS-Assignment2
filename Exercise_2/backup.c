#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>

#define BUFFER 1024

// Function which creates a hard link between two files
void createHardlink(const char *src, const char *dst) {
    if (link(src, dst) == -1) {
        perror("hardlink");
    }
}
// Function which creates a symlink between two files
void copySymlink(const char *src, const char *dst) {
    char target[BUFFER];
    int len = readlink(src, target, sizeof(target) - 1);
    if (len == -1) {
        perror("readlink");
        return;
    }
    target[len] = '\0';
    if (symlink(target, dst) == -1) {
        perror("symlink");
    }
}
// Function which creates a directory, when given a path
void copyDirectory(const char *dst) {
    mkdir(dst, 0777);
}

// The main recursive function which will scan the entire directory, and every directory within it
void scanDirectory(const char *srcPath, const char *dstPath) {

    // Setting up variables
    DIR *srcDir = opendir(srcPath);
    if (!srcDir) {
        perror("opendir");
        return;
    }
    struct dirent *rootDir;
    struct stat sb;

    // Looping through all the contents of the source directory
    while ((rootDir = readdir(srcDir)) != NULL) {
        if (strcmp(rootDir->d_name, ".") == 0 || strcmp(rootDir->d_name, "..") == 0) {
            continue;
        }
        // Creating a string which will have the full path of our current source directory and dst directory
        char srcFull[BUFFER], dstFull[BUFFER];
        snprintf(srcFull, BUFFER, "%s/%s", srcPath, rootDir->d_name);
        snprintf(dstFull, BUFFER, "%s/%s", dstPath, rootDir->d_name);

        // Checking whether stat worked
        if (lstat(srcFull, &sb) == -1) {
            perror("stat failed");
            continue;
        }
        // Now checking what type of file did we encounter
        // In case of a directory, copy it to the destination, and run a recursion from that directory
        if (S_ISDIR(sb.st_mode)) {
            copyDirectory(dstFull);
            printf("Directory: %s\n", srcFull);
            scanDirectory(srcFull, dstFull);
        }
        // In case of a symlink, creates a symlink
        else if (S_ISLNK(sb.st_mode)) {
            copySymlink(srcFull, dstFull);
        }
        // In case of a regular file (hard link) creates a hard link
        else if (S_ISREG(sb.st_mode)) {
            createHardlink(srcFull, dstFull);
        }
        // If it's not any of the above, idk what to do
        else {
            continue;
        }
    }
    closedir(srcDir);
}

int main(int argc, char *argv[]) {

    // In case the args count is not correct, exit the program
    if (argc != 3) {
        printf("wrong args count inserted!\n");
        printf("usage: ./backup <src_dir> <backup_dir>\n");
        exit(1);
    }
    // Checking whether the source directory exists, if not, throw the user out
    DIR *srcDir = opendir(argv[1]);
    if (srcDir == NULL) {
        perror("src dir\n");
        exit(1);
    };
    // Checking whether the source directory exists, if it does, throw the user out
    if (mkdir(argv[2], 0777) == -1) {
        perror("backup dir\n");
        exit(1);
    }
    // Running the main recourse function
    scanDirectory(argv[1], argv[2]);
    return 0;
}