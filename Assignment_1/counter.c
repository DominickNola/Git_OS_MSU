#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

int main(int argc, char *argv[]) {

    int child_pid = getpid();
    assert(child_pid >= 0);
    int parent_pid = getppid();
    assert(parent_pid >= 0);
    char *end_pointer;

    int str_to_int = strtol(argv[1], &end_pointer, 10);

    assert(printf("Parent PID: %d\n", parent_pid) >= 0);
    for(int loop = 1; loop <= str_to_int; loop++)
    {
        usleep(250000); // sleep for 1/4 of a second.
        assert(printf("Process: %d %d\n", child_pid, loop) >= 0);
    }

    return str_to_int;
}
