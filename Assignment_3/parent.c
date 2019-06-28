#include <unistd.h>
#include <assert.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "syscall.h"
#include <sys/errno.h>

void signal_handler();
void sigchld();
void sighup();
void sigusr1();
void sigusr2();
void invalid();
int signum;
int fork_child;

int main() {

    struct sigaction action;
    action.sa_handler = signal_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_RESTART | SA_NOCLDSTOP;

    assert(sigaction(SIGUSR1, &action, NULL) == 0);
    assert(sigaction(SIGUSR2, &action, NULL) == 0);
    assert(sigaction(SIGHUP, &action, NULL) == 0);
    assert(sigaction(SIGCHLD, &action, NULL) == 0);

    int exit_status;
    fork_child = fork();
    if(fork_child < 0) {

        perror("fork() error.\n");
        exit(-1);
    } else if(fork_child == 0) {

        exit_status = execl("./child", "child", NULL);
        perror("execl() error.\n");
        exit(exit_status);
    } else {

        for(int loop = 1; loop <= 1; loop++) {
            WRITESTRING("The parent is going to SIGSTOP the child.\n");
            assert(kill(fork_child, SIGSTOP) == 0);
            assert(sleep(2) == 0);
            errno = 0;
            WRITESTRING("The parent is going to SIGCONT the child.\n");
            assert(kill(fork_child, SIGCONT) == 0);
            assert(sleep(2) == 0);
            errno = 0;
        }

        assert(kill(fork_child, SIGINT) == 0);
        assert(pause() == 0); // sigchld() auto called
    }

    return 0;
}

void signal_handler(int signal) {

    // Signal dictionary that calls the corresponding functions.
    static void(*dict[32])(void) = {invalid, sighup, invalid, invalid, invalid,
                                    invalid, invalid, invalid, invalid, invalid,
                                    sigusr1, invalid, sigusr2, invalid, invalid,
                                    invalid, sigusr1, sigchld, sigchld, invalid,
                                    sigchld, invalid, invalid, invalid, invalid,
                                    invalid, invalid, invalid, invalid, invalid,
                                    sigusr1, sigusr2};
    signum = signal;
    // Print signal number for troubleshooting different platforms.
    // WRITEINT(signum, 5);
    // WRITESTRING("\n");
    dict[signal]();
}

void sigchld() {

    int cpid = fork_child;
    assert((waitpid(-1, &fork_child, 0)) != 0);
    if (WIFSIGNALED(fork_child)){
        int child_status = WTERMSIG(fork_child);
        WRITESTRING("SIGCHLD: Process");
        WRITEINT(cpid, 7);
        WRITESTRING(" exited with status: ");
        WRITEINT(child_status, 2);
        WRITESTRING("\n");
    }

    exit(0);
}

void sighup() {

    assert(write(STDOUT_FILENO,
                 "Signal# 1, SIGHUP = SIGNAL HANGUP.\n", 35) != 0);
}

void sigusr1() {

    assert(write(STDOUT_FILENO,
                 "Signal# 30 || 10 || 16, SIGUSR1 = USER DEFINED 1.\n", 50) != 0);
}

void sigusr2() {

    assert(write(STDOUT_FILENO,
                 "Signal# 31 || 12, SIGUSR2 = USER DEFINED 2.\n", 50) != 0);
}

void invalid() {

    assert(write(STDOUT_FILENO, "Signal is invalid.\n", 19) != 0);
}
