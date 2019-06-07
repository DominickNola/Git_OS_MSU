#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

int main(int argc, char *argv[]) {

    int child_pid = getpid();
    int parent_pid = getppid();

    char *end;
    int str_to_int = strtol(argv[1], &end, 10);

    assert(printf("Parent PID: %d\n", parent_pid) != 0);
    for(int i = 1; i <= str_to_int; i++)
    {
        usleep(250000); // sleep for 1/4 of a second.
        assert(printf("Process: %d %d\n", child_pid, i) != 0);
    }

    return str_to_int;
}
