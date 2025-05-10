#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER 1000

// Checks the length of an input in a file
int checkFileLength(FILE** data) {
    // Resets the current pointer to the file back to the start
    fseek(*data, 0, SEEK_SET);
    char input[BUFFER];
    fscanf(*data, "%s", input);
    // Resets the current pointer to the file back to the start after we checked its length
    fseek(*data, 0, SEEK_SET);
    return strlen(input);
}

// Function which will read the file
void readFile(FILE **srcFile, FILE **destFile, int startOffset, int endOffset) {
    //Checking edge cases:
    if (startOffset > endOffset) {
        printf("The start offset is greater than the end offset. why u bully me? :(\n");
        return;
    }
    if (startOffset < 0) {
        printf("The start offset is lesser than 0. why u bully me? :(\n");
        return;
    }
    if (endOffset > checkFileLength(srcFile)) {
        printf("%d\n", checkFileLength(srcFile));
        printf("%d\n", endOffset);
        printf("The end offset is greater than the length of the data file. why u bully me? :(\n");
        return;
    }
    char read[BUFFER];
    fscanf(*srcFile, "%s", read);
    printf("%s\n", read);
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
    }

    // Main reading through requests file loop
    char input[BUFFER];
    while (fscanf(requests, "%s ", input) != EOF) {
        printf("%s\n", input);
    }

    printf("hi\n");
}