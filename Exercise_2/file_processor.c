#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

// Function which will read the file
void readFile() {

}

// Function which will write into the file
void writeFile() {

}

// Function which will quit
void quit() {

}

int main(int argc, char *argv[]) {

    // In case the args count is not correct, exit the program
    if (argc != 3) {
        printf("wrong args count inserted!\n");
        printf("usage: ./file_processor <data_file.txt> <request_file.txt>\n");
        exit(1);
    }

    // Checks if the data file exists, and if it does, opens it for reading and writing
    FILE *data = fopen(argv[1], "r+");
    if (data == NULL) {
        perror("data.txt\n");
        exit(1);
    };
    // Checks if the requests file exists, and if it does, opens it for reading
    FILE *requests = fopen(argv[2], "r");
    if (requests == NULL) {
        perror("requests.txt\n");
        exit(1);
    };

    printf("hi\n");
}