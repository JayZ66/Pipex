
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t pid;

    pid = fork(); // Fork a new process
    if (pid == -1)
    {
        perror("fork"); // If fork fails, output the error
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) // Child process
    {
        printf("I am the child process.\n");
        sleep(2); // Child process sleeps for 2 seconds
        exit(EXIT_SUCCESS); // Exit child process
    }
    else // Parent process
    {
        printf("I am the parent process.\n");
        wait(NULL); // Parent process waits for the child to terminate
        //int status;
        //waitpid(pid, &status, 0);
        printf("Child process terminated after a 2s delay.\n");
    }

    return (EXIT_SUCCESS);
}

/*
Key Concepts:
- sleep(): Suspends execution of the calling process for a specified number of seconds.
  In this code, the child process sleeps for 2 seconds. This does not consume CPU resources.

- wait(): Makes the parent process wait until all of its child processes terminate.
  If wait(NULL) is used, as in this code, the parent process waits for any child process to end.
  The wait() function is useful for preventing zombie processes and ensuring proper process cleanup.

- The combination of fork(), sleep(), and wait() demonstrates process creation, 
  timed execution, and synchronization between parent and child processes in Unix-like systems.
*/


/*
In this chapter, we'll see how to actually wait for processes to
finish !
*/

int main(int argc, char *argv[])
{
    int id = fork();
    int n; // The nb that we start at.
    if (id == 0)
        n = 1; 
    else
        n = 6;
    int i;
    for (i = n; i < n + 5, i++)
    {
        printf("%d\n", i);
        fflush(stdout);
    }
    return (0);
}

/*
Just want, first, two processes.
Then we want to print all nb from 1 to 10.
First, we want the five to be printed by the child process.
Second, we want the last ones to be print by the main process.

Steps : 
- Create a var. n, which is the nb we start at.
- We check if we are in the main process.Bce if we are in, it'll start at 6.
On the contrary, it'll start at 1.
- Else, we could be either in the main or the child process.
But here, we're definitely in the main process.
- Then, create a loop that goes through all the nb.
- In the loop, we print all the nb but with the standard output,
whenever we print off something to it has an internal buffer.
So if we print a lot of things quickly, it'll wait to get all the inputs,
and then print print everything at once.
Or, here we want to print each nb at each call.
fflush(stdout) ==> So, each time we print a nb/digit, it's going to be shown on the terminal.

Result : 1 6 2 7 3 8 4 9 5 10 ==> Pq pas dans l'ordre ?
On a des processus simultanés, donc ils exécutent tous les deux chaque instruction en même temps.
Ils arrivent au même moment dans la loop, donc print "ensemble".
> Main process print 1 et child process print 6, like ping-pong executing all the statements.
*/

int main(int argc, char *argv[])
{
    int id = fork();
    int n; // The nb that we start at.
    if (id == 0)
        n = 1; 
    else
        n = 6;
    if (id != 0) // If we're not in the child process.
        wait();
    int i;
    for (i = n; i < n + 5, i++)
    {
        printf("%d\n", i);
        fflush(stdout);
    }
    return (0);
}

/*
So, how can we stop this "ping-pong" execution to get nb in the right order ?
=> The wait() function comes in !
What wait does ? 
Stop the execution until the child has finished executing.
So here, wait for the child process to print his nb and then let the parent
process to print his nb. => Here, we're not specifying which child process.
When child process is done, it'll get his memory deallocate.

Warning : if we just let the wait function, the child process will be
stuck as it doesn't have another child process (his own).
=> So, we have to specify that we're in the main process.

What does wait() function ?
It will allow to order the execution of processes you got first the child
and then the main process. Otherwise, they will be simultaneous (intertwined).
*/