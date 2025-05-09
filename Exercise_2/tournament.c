#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUM_GLADIATORS 4

int main(int argc, char *argv[]) {

    // Setting up gladiator names, file names (stats for the gladiators), their respective PIDS, and an array
    // To save all the pids of gladiators which died in glorious combat
    char* gladiator_names[NUM_GLADIATORS] = {"Maximus", "Lucius", "Commodus", "Spartacus"};
    char* gladiator_files[NUM_GLADIATORS] = {"G1.txt", "G2.txt", "G3.txt", "G4.txt"};
    pid_t gladiator_pids[NUM_GLADIATORS];
    pid_t defeated_gladiator_pids[NUM_GLADIATORS-1];


    // Creating the gladiators using exec with gladiator.c
    for (int i = 0; i < NUM_GLADIATORS; i++) {
        gladiator_pids[i] = fork();
        if (gladiator_pids[i] == 0) {
            // Replace the child process with the gladiator program
            char *args[] = {"./gladiator", gladiator_files[i], NULL};
            execvp(args[0], args);
            perror("execv failed");
            exit(1);
        }
    }

    // We wait for each defeated gladiator, and save their PIDS in an array, to remember which lost
    defeated_gladiator_pids[0] = wait(NULL);
    defeated_gladiator_pids[1] = wait(NULL);
    defeated_gladiator_pids[2] = wait(NULL);

    // We will track the index of the last gladiator which was left standing with 'winner'
    int winner = 0;
    // If that index is not on the list of the defeated gladiators, then this gladiator has obviously won
    for (;winner < NUM_GLADIATORS; winner++) {
        if (gladiator_pids[winner] != defeated_gladiator_pids[0] &&
                gladiator_pids[winner] != defeated_gladiator_pids[1] &&
                gladiator_pids[winner] != defeated_gladiator_pids[2]) {
            break;
        }
    }

    printf("The gods have spoken, the winner of the tournament is %s!\n", gladiator_names[winner]);

    return 0;
}