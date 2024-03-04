
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
This chapter : 
Going step by step through the code & with the memory
that each process has & show exactly what's going on behind
the scenes. 
*/

/*
Step by step : parallel execution of both processus.
- int id = fork();
This line says that ID equals fork.
What does fork ? 
It actually creates a child process from the main process.
And that child process is very important bce it has the exact same memory
as the main/parent process (everything is copied).

Memory visualization : 
=> They get the same values, but the memory place where they are 
allocated is different. So, if you change a var. in one, it'll 
not change in the other process.
=> So, each process has a copy of its own variables (same at the start).
*/

/*
Step by step : parent process
1. int id = fork();
    int n;
- Parent process memory
    argc = 1, argv = "main.exe", n = ?, id = ?
2. if (id == 0)
When this line of code is executed in the parent process,
it'll also be executed in the child process.
 So, in the parent process the ID was set to something 4300, 
it represents the process ID of the child process.
    ==> The ID is not zero so : 
3. else
    n = 6;
        argc = 1, argv = "main.exe", n = 6, id = 4300;
We get to the else branch, so our n is equal to 6.
4. if (id != 0)
Check if we're on parent or child process. => So here, the ID isn't 0.
5. wait();
So here, we call wait() function. 
=> It says, completely stop the execution until a child process has
finished its executions.
So, it'll wait there until we get to the return (0) of the child processus.
6. int i;
Now, that the child p. is over, the parent p. can continue is execution.
7. int  i;
    for (i = n; i < n + 5; i++)
It can now go inside the loop. 
So, n is here equal to 6 and i is equal to n. Until i < 11.
So, we're going to just print every single nb from 6 up to 10.
8. if (id != 0)
    printf("\n");
It's going to check if our ID, that we got from fork, is different of 0.
Yes, here it's equal to 4300, so we print a line break.
8. return (0);
    argc = 1, argv = "main.exe", n = 6, id = 4300, i = 11;
We executed both of the processes, & the parent process waited for the
child to finish his execution first before continue its own.
*/

/*
Step by step : child process
1. int id = fork();
    int n;
- Child process memory
    argc = 1, argv = "main.exe", n = ?, id = ?
2. if (id == 0)
Executed when parent process executed it. (not always like this)
In the child process, the ID is set to 0 bce it's a child.
    ==> The ID is zero so : 
3. n = 1;
    argc = 1, argv = "main.exe", n = 1, id = 0;
If we ask, when we're in the child p. if ID is zero, we do.
So, n is equal to 1. 
4. if (id != 0)
Another check for the ID to figure out if we're on the child or parent process.
But here, the ID is 0, so we skip this condition.
5. int  i;
    for (i = n; i < n + 5; i++)
So, starts the loop with i equals to N (so 1), so less than 6 (condition).
6. printf("%d", i);
    fflush(stdout);
So, we're going to just print every single nb from 1 up to 5.
And each time we call printf (thx to fflush).
7. if (id != 0)
    printf("\n");
So, in the child process the ID is actually zero so no condition.
8. return (0);
    argc = 1, argv = "main.exe", n = 1, id = 0, i = 6;
So, the child process is over, now it's time to the parent process
to start again.
*/

/*
Conclusions : 
1. The memory is getting copied value by value, variable by variable from
one process to another, when you do fork().
They are going to be exactly the same in both processes.
BUT when you execute it, each of the process has their own actual space
in memory.
SO, when modifies  a var., the other one doesn't necessarily have the same value.

2. Both processes in this situation actually execute the same exact code.
Once fork is called, the execution line gets split & you start executing
the same lines of code but with different results bce of that ID.
Depending on which process we are, we do different things.
BUT, we also do some common things.
*/