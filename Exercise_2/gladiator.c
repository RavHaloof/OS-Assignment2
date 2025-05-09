#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define OPPONENT_COUNT 3
#define FILE_VARIABLES 5

int main(int argc, char *argv[]) {

    // In case the args count is not correct, exit the program
    if (argc != 2) {
        printf("wrong args count inserted!");
        printf("usage: ./gladiator <stat_file>");
        exit(1);
    }
    // Opening our given file, and setting the flag to only read it
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        printf("Opening the file %s failed! exiting...", argv[1]);
    }

    // Setting up variables for the gladiator
    int health;
    int opponent_name[OPPONENT_COUNT], opponent_attack[OPPONENT_COUNT], file_nums[FILE_VARIABLES];
    pid_t pid;
    char buffer[BUFFER_SIZE];

    // Reading the data in the gladiator file
    ssize_t bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
    if (bytes_read < 0) {
        perror("Read failed");
        close(fd);
        return 1;
    }
    // Adding an empty char to the end of the string to make sure that we know when we finished reading it
    buffer[bytes_read] = '\0';


    // Separating between each comma, and saving each number
    char *token = strtok(buffer, ",");
    for (int i = 0; i < FILE_VARIABLES; i++) {
        file_nums[i] = atoi(token);
        token = strtok(NULL, ",");
    }

    for (int i = 0; i < FILE_VARIABLES; ++i) {
        printf("From file: %s, stats: %d\n", argv[1], file_nums[i]);
    }

    //
    // Open the log file in append mode
    /*
    while (health > 0) {
        FILE *logFile = fopen("gladiator_log.txt", "a");
        for (int i = 0; i < 3; i++) {
            fprintf(logFile, "Facing opponent %d... Taking %d damage\n", opponent_name[i], opponent_attack[i]);
            health -= opponent_attack[i];
            if (health > 0) {
                fprintf(logFile, "Are you not entertained? Remaining health: %d\n", health);
            } else {
                fprintf(logFile, "The gladiator has fallen... Final health: %d\n", health);
                break;
            }
        }
    }
     */
    return 0;

}