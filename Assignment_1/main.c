#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

int main() {

    char string_num[10] = "3";
    int fork_result = fork();
    int exit_status;
    if(fork_result  < 0) {
        perror("fork()error!\n\n");
        exit(-1);
    } else if(fork_result == 0) {

        // child process block
        assert(printf("\nChild PID: %d\n", getpid()) != 0);
        execl("./counter", "counter", string_num, (char*)NULL);
        perror("execl()error!\n\n");
        exit(1);
    } else {

        // parent process block
        wait(&exit_status);
        assert(printf("Process %d exited with status: %d\n\n", fork_result, WEXITSTATUS(exit_status)) != 0);
    }

    return 0;
}
