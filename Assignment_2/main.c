#include <unistd.h>
#include <assert.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

void SIGUSR1_Handler();
void SIGUSR2_Handler();
void SIGHUP_Handler();

int main() {

    signal(SIGUSR1, SIGUSR1_Handler);
    signal(SIGUSR2, SIGUSR2_Handler);
    signal(SIGHUP, SIGHUP_Handler);
    printf("inside main.c\n");
    int exitStatus;
    // pid_t parentPID;
    pid_t fork_child = fork();

    if( fork_child < 0) {

        perror("fork() error.\n");
        exit(-1);
    } else if(fork_child == 0) {

        printf("inside child.\n");
        exitStatus = execl("./child", "child", NULL);
        perror("execl() error.\n");
        exit(exitStatus);
    } else {

        assert(waitpid(fork_child, &exitStatus, 0) != -1);
        printf("inside else, child done.\n");
    }

    return 0;

}

void SIGUSR1_Handler(int signal) {

    //sigaction();
    printf("SIGUSR1_Handler: ");
    printf("User defined process 1.\n");
    //then wait for the child
    //waitpid();
    //and then when signals arrive, the signal handler begins doing its thing.

}

void SIGUSR2_Handler(int signal) {

    printf("SIGUSR2_Handler: ");
    printf("User defined process 2.\n");

}

void SIGHUP_Handler(int signal) {

    printf("SIGHUP: ");
    printf("HANGUP or DEATH DETECTED!\n");
}
