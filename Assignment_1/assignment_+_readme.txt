READ-ME:
To run programs: 
1) From Terminal, compile each program: 
($ gcc -0 counter counter.c)
($ gcc -0 main main.c)
2) Run the main: 
To use the Hardcoded Value: ($ ./main) 
or to use the Terminal Input ($ ./main 9).

ASSIGNMENT:
Due date: Monday, June 10, 2019, 11:55 PM
Maximum number of files: 2
Type of work: Individual work
Create two C programs.

Have the first read a single argument that is the string representation of an integer.
Loop that many times and display "Process: PID #" where PID is the process identifier
and # is from 1 through n (n from the first argument). Also, have this program return
n as its status. Name this program counter.c.

Have the second create a child process and then execute the first program, passing an
argument of 5. Have this program wait for the child process exit and report its status.
Name this program main.c

Your output should look similar to:

Child PID: 82336
Parent PID: 82335
Process: 82336 1
Process: 82336 2
Process: 82336 3
Process: 82336 4
Process: 82336 5
Process 82336 exited with status: 5

The most relevant manual pages(man pages) include sleep(3), execl(3), wait(2),
perror(3), fork(2), exit(3), getpid(2), getppid(2), and strtol(3).

For all system calls, including f/printf(), you need to pay attention to the
return value.  I suggest something like:
#include <assert.h>
[...]
assert (printf ("...") != 0);

For perror's, I recommend simply putting in the system call that failed, for example:
perror ("waitpid");

