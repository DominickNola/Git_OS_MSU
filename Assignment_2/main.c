#include <unistd.h>
#include <assert.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void signal_handler();
void sighup();
void sigusr1();
void sigusr2();
void invalid();

int main() {

    clock_t time;
    time = clock();
    int exit_status;

    struct sigaction action;
    action.sa_handler = signal_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_RESTART;

    assert(sigaction(SIGUSR1, &action, NULL) == 0);
    assert(sigaction(SIGUSR2, &action, NULL) == 0);
    assert(sigaction(SIGHUP, &action, NULL) == 0);

    pid_t fork_child = fork();
    if(fork_child < 0) {

        perror("fork() error.\n");
        exit(-1);
    } else if(fork_child == 0) {

        exit_status = execl("./child", "child", NULL);
        perror("execl() error.\n");
        exit(exit_status);
    } else {

        assert(waitpid(fork_child, &exit_status, 0) != -1);
    }

    time = clock() - time;
    double time_taken = ((double)time)/CLOCKS_PER_SEC;
    printf("\n%f seconds to execute\n", time_taken);
    return 0;
}

void signal_handler(int signal) {

    static void(*dict[32])(void) = {invalid, sighup, invalid, invalid, invalid, invalid, invalid, invalid, invalid,
                                    invalid, sigusr1, invalid, sigusr2, invalid, invalid, invalid, sigusr1, sigusr2,
                                    invalid, invalid, invalid, invalid, invalid, invalid, invalid, invalid, invalid,
                                    invalid, invalid, invalid, sigusr1, sigusr2};
    dict[signal]();
}

void sighup() {

    assert(write(STDOUT_FILENO, "Signal# 1, SIGHUP = SIGNAL HANGUP.\n", 35) != 0);
}

void sigusr1() {

    assert(write(STDOUT_FILENO, "Signal# 30 || 10 || 16, SIGUSR1 = USER DEFINED 1.\n", 50) != 0);
}

void sigusr2() {

    assert(write(STDOUT_FILENO, "Signal# 31 || 12 || 17, SIGUSR2 = USER DEFINED 2.\n", 50) != 0);
}

void invalid() {

    assert(write(STDOUT_FILENO, "Signal is invalid.\n", 19) != 0);
}
