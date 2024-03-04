
/*
In this chapter : Waitpid() function
What does this function ? 
It's instead of just waiting for whatever child
process to finish execution, it's going to wait for
a specific child p. to finish its execution.
*/

int main(int argc, char *argv[])
{
    int pid1 = fork();
    if (pid1 == -1)
        return (1);
    if (pid == 0)
    {
        sleep(4);
        printf("Finished execution (%d)\n", getpid());
    }
    int pid2 = fork();
    if (pid2 == -1)
        return (1);
    if (pid2 == 0)
    {
        sleep(1);
        printf("Finished execution (%d)\n", getpid());
    }
    wait(NULL);
    wait(NULL);
    return (0);
}

/*
We are going to create 2 child processes. And inside each process
we want to do : 
- Is in one of them, we're going to wait a certain amount of time.
With the function sleep(), for the 1st we'll wait 4s & the 2nd 1s.
- After that, we're going to print a message, to print the Pid.
So, normally one will be slower than the other one.
- Then, we must wait for them, so if we just try to call wait(NULL)
twice, so that's good. The child p. with one second will be faster
than the other one, so in a good "order".

*/

int main(int argc, char *argv[])
{
    int pid1 = fork();
    if (pid1 == -1)
        return (1);
    if (pid == 0)
    {
        sleep(4);
        printf("Finished execution (%d)\n", getpid());
    }
    int pid2 = fork();
    if (pid2 == -1)
        return (1);
    if (pid2 == 0)
    {
        sleep(1);
        printf("Finished execution (%d)\n", getpid());
    }
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return (0);
}

/*
But what if we want it to be the other way around ?
If we want to first wait for the longest running process,
which is the one with 4 seconds.
=> That could be done using waitpid() function, it'll take different args.
1. The process ID, that we want to wait for.
2. The same as the arg. for wait.
3. Are some parameters that you can pass telling it how to wait.
It's like a flag, for ex. WNOHANG, means that's not gonna wait for the process
to finish execution, it's just gonna check if it finished execution.

After, we will do the same for the 2nd child p. that is the
fastest one.
*/

/*
TIPS - The value of pid can be (when we don't put pid.) :
1. A negative number => Instead of waiting for that specific process
id is gonna wait for that specific process group id. 
And usually most processes have the same group id.
2. -1 => Means that the same as using the wait() function, it'll
wait on any child process.
3.c 0 => Wait for anyer child process with the same process group id.
4. > 0 number => If you're passing a nb that's higher than zero, it's
just gonna wait for that process id.
*/