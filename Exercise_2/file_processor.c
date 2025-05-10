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
int readFile(FILE **srcFile, FILE **destFile, int startOffset, int endOffset) {
    //Checking edge cases:
    if (startOffset > endOffset) {
        printf("The start offset is greater than the end offset. why u bully me? :(\n");
        return 0;
    }
    if (startOffset < 0) {
        printf("The start offset is lesser than 0. why u bully me? :(\n");
        return 0;
    }
    if (endOffset > checkFileLength(srcFile)) {
        printf("The end offset is greater than the length of the data file. why u bully me? :(\n");
        return 0;
    }
    // We set the start point to the start offset using fseek
    char read[BUFFER];
    fseek(*srcFile, startOffset, SEEK_SET);
    // We print char by char into the destination file from the start offset to the end offset
    for (int i = 0; i <= endOffset - startOffset; ++i) {
        fscanf(*srcFile, "%c", read);
        fprintf(*destFile, "%c", read[0]);
    }
    // Resetting the start point now that we've finished reading
    fseek(*srcFile, 0, SEEK_SET);
    return 1;
}

// Function which will write into the file
void writeFile(FILE **destFile, int startOffset, char* string) {
    //Checking edge cases:
    if (startOffset < 0) {
        printf("The start offset is lesser than 0. why u bully me? :(\n");
        return;
    }
    if (startOffset > checkFileLength(destFile) + 1) {
        printf("The end offset is greater than the length of the data file. why u bully me? :(\n");
        return;
    }

    // Creating a new file where we will store the new data in
    FILE *data_temp = fopen("data_temp.txt", "w+");
    // Writing all the data up to the offset point
    readFile(destFile, &data_temp, 0, startOffset);

    // Printing the string at the offset point
    fseek(data_temp, startOffset, SEEK_SET);
    fprintf(data_temp, "%s", string);

    // Printing the rest of the original file into the temp file after the string we just printed into the temp file
    fseek(data_temp, startOffset + strlen(string), SEEK_SET);
    readFile(destFile, &data_temp, startOffset, checkFileLength(destFile) - 1);

    // We return the pointers back to the beginning of each file for the final copy
    fseek(*destFile, 0, SEEK_SET);
    fseek(data_temp, 0, SEEK_SET);

    // Now we copy back the data from the temporary file into the destination file
    char read[BUFFER];
    fscanf(data_temp, "%s", read);
    fprintf(*destFile, "%s", read);

    // We delete the temporary file, since we have no more use for it
    fclose(data_temp);
    remove("data_temp.txt");
}

// Function which will quit
void quit() {
    exit(0);
}

int main(int argc, char *argv[]) {

    // In case the args count is not correct, exit the program
    if (argc != 3) {
        printf("wrong args count inserted!\n");
        printf("usage: ./file_processor <data_file.txt> <request_file.txt>\n");
        exit(1);
    }

    // Checks if the data file exists, and if it does, opens it for reading and writing
    FILE *dataFile = fopen(argv[1], "r+");
    if (dataFile == NULL) {
        perror("data.txt\n");
        exit(1);
    };
    // Checks if the requests file exists, and if it does, opens it for reading
    FILE *requestsFile = fopen(argv[2], "r");
    if (requestsFile == NULL) {
        perror("requests.txt\n");
        exit(1);
    }

    FILE *resultsFile = fopen("read_results.txt", "w");
    char input[BUFFER];
    char var1[BUFFER];
    char var2[BUFFER];
    // Main reading through requests file loop
    while (fscanf(requestsFile, "%s ", input) != EOF) {
        // In case the user requested to read
        if (strcmp(input, "R") == 0) {
            fscanf(requestsFile, "%s %s", var1, var2);
            if (readFile(&dataFile, &resultsFile, atoi(var1), atoi(var2))) {
                // Then we go down a line
                fprintf(resultsFile, "\n");
            }
        }
        // In case the user requested to write
        else if (strcmp(input, "W") == 0) {
            fscanf(requestsFile, "%s %s", var1, var2);
            writeFile(&dataFile, atoi(var1), var2);
        }
        // In case the user requested to quit
        else if (strcmp(input, "Q") == 0) {
            quit();
        }
        // Otherwise (invalid command)
        else {
            printf("invalid request!\n");
        }
    }

    printf("run finished!\n");
}