#include <unistd.h>
#include <assert.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main() {

    pid_t ppid = getppid();

    assert(kill(ppid, SIGUSR2) == 0);
    assert(kill(ppid, SIGHUP) == 0);
    assert(kill(ppid, SIGUSR1) == 0);
    assert(kill(ppid, SIGUSR1) == 0);
    assert(kill(ppid, SIGUSR1) == 0);

    return 0;
}
