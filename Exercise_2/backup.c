#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>

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
    DIR *backupDir = opendir(argv[2]);
}