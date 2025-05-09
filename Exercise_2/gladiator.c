#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    // In case the args count is not correct, exit the program
    if (argc != 2) {
        printf("wrong args count inserted!");
        printf("usage: ./gladiator <stat_file>");
        exit(1);
    }

    printf("hi");

    /*
     // Open the log file in append mode
    while (health > 0) {
        FILE *logFile = fopen("gladiator_log.txt", "a");
        for (int i = 0; i < 3; i++) {
            int opponent_attack = 1;
            fprintf(logFile, "Facing opponent %d... Taking %d damage\n", opponents[i], opponent_attack);
            health -= opponent_attack;
            if (health > 0) {
                fprintf(logFile, "Are you not entertained? Remaining health: %d\n", health);
            } else {
                fprintf(logFile, "The gladiator has fallen... Final health: %d\n", health);
                break;
            }
        }
    }
    return 0;
     */
}