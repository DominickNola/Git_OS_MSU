#include <unistd.h>
#include <assert.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main() {

    int return_value;
    pid_t ppid = getppid();

/*
    struct sigaction action;
    action.sa_handler = handler;
    sigemptyset (&action.sa_mask);
    action.sa_flags = SA_RESTART;
    assert (sigaction (SIGUSR1, &action, NULL) == 0 );
*/

    kill(ppid, SIGUSR1);
    kill(ppid, SIGUSR1);
    kill(ppid, SIGUSR1);
    kill(ppid, SIGUSR2);
    kill(ppid, SIGHUP);

    return return_value;
}

