#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

int main(int argc, char *argv[]) {

    char *terminal_input = argv[1];
    char string_num[10];
    int fork_child = fork();
    int exit_status;

    if(terminal_input == NULL) {
        memcpy(string_num, "5", sizeof("5") + 1);
    } else {
        memcpy(string_num, argv[1], sizeof(terminal_input) + 1);
    }

    if(fork_child  < 0) {

        perror("fork() error!\n\n");
        exit(-1);
    } else if(fork_child == 0) {

        // child process
        assert(printf("\nChild PID: %d\n", getpid()) >= 0);
        execl("./counter", "counter", string_num, (char*)NULL);
        perror("execl() error!\n\n");
        exit(1);
    } else {

        // parent process
        assert(waitpid(-1, &exit_status, 0) != 0);
        if(WIFEXITED(exit_status)) {
            assert(printf("Process %d exited with status: %d\n\n", fork_child,
                          WEXITSTATUS(exit_status)) >= 0);
        }
    }

    return 0;
}
