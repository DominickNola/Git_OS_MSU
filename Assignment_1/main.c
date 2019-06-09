#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <wait.h>


int main(int argc, char *argv[]) {

    // toggle between hard coded "5"(./main) and terminal input(./main 8).
    char string_num[10];
    if(argv[1] == NULL) {
        memcpy(string_num, "5", sizeof("5") + 1);
    } else {
        memcpy(string_num, argv[1], sizeof(argv[1]) + 1);
    }

    // create the child.
    int fork_result = fork();
    int exit_status;
    if(fork_result  < 0) {
        perror("fork() error!\n\n");
        exit(-1);
    } else if(fork_result == 0) {

        // child process block
        assert(printf("\nChild PID: %d\n", getpid()) != 0);
        execl("./counter", "counter", string_num, (char*)NULL);
        perror("execl() error!\n\n");
        exit(1);
    } else {

        // parent process block
        // waitpid(-1, &exit_status, 0);
        wait(NULL);
        assert(printf("Process %d exited with status: %d\n\n", fork_result, WEXITSTATUS(exit_status)) != 0);
    }

    return 0;
}

