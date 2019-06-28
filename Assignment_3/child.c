#include <unistd.h>
#include <assert.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include "syscall.h"
#include <sys/errno.h>

int main() {

    pid_t cpid = getpid();

    while(1) {

        WRITESTRING("Awake in ");
        WRITEINT(cpid, 6);
        WRITESTRING("\n");
        assert(sleep(1) == 0);
        errno = 0;
    }

    return 0;
}
