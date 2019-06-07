#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

int main(int argc, char *argv[]) {

    // toggle between terminal input(./main 6) and hard coded value(./main).
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
        wait(&exit_status);
        assert(printf("Process %d exited with status: %d\n\n", fork_result, WEXITSTATUS(exit_status)) != 0);
    }

    return 0;
}
