#include <unistd.h>
#include <assert.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

void signal_handler();

int main() {

    int exit_status;

    struct sigaction action;
    action.sa_handler = signal_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_RESTART;

    assert(sigaction(SIGUSR1, &action, NULL) == 0);
    assert(sigaction(SIGUSR2, &action, NULL) == 0);
    assert(sigaction(SIGHUP, &action, NULL) == 0);

    pid_t fork_child = fork();
    if( fork_child < 0) {

        perror("fork() error.\n");
        exit(-1);
    } else if(fork_child == 0) {

        exit_status = execl("./child", "child", NULL);
        perror("execl() error.\n");
        exit(exit_status);
    } else {

        assert(waitpid(fork_child, &exit_status, 0) != -1);
    }

    return 0;
}

void signal_handler(int signal) {

<<<<<<< HEAD
    //sigaction();
    printf("SIGUSR1_Handler: ");
    printf("User defined process 1.\n");
    //then wait for the child
    //waitpid();
    //and then when signals arrive, the signal handler begins doing its thing.
=======
    if(signal == 1) {
>>>>>>> 420f75bc4425f974880d6dd9ed377da681d7c937

        assert(write(STDOUT_FILENO, "Signal# 1, SIGHUP = SIGNAL HANGUP.\n", 35) != 0);

    } else if(signal == 30) {

<<<<<<< HEAD
    printf("SIGUSR2_Handler: ");
    printf("User defined process 2.\n");
=======
        assert(write(STDOUT_FILENO, "Signal# 30, SIGUSR1 = USER DEFINED 1.\n", 39) != 0);
>>>>>>> 420f75bc4425f974880d6dd9ed377da681d7c937

    } else if(signal == 31) {

        assert(write(STDOUT_FILENO, "Signal# 31, SIGUSR2 = USER DEFINED 2.\n", 39) != 0);

    } else {

        assert(write(STDOUT_FILENO, "Signal is invalid.\n", 19) != 0);
    }

     // maybe make 1 handler per signal
     // Future dictionary/array of signal functions.
//    char *dict[32] = {"invalid", "SIGHUP", " ", " ", " ", " ", " ",
//                      " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
//                      " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
//                      " ", " ", " ", "SIGUSR1", "SIGUSR2"};
//
//    printf("Signal# %d, %s\n", signal, dict[signal]);

<<<<<<< HEAD
    printf("SIGHUP: ");
    printf("HANGUP or DEATH DETECTED!\n");
=======
>>>>>>> 420f75bc4425f974880d6dd9ed377da681d7c937
}
