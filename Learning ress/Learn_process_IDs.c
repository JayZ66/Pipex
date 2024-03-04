
/*
Chapter : Learn our process IDs.

As the name implies, they are just IDs (identification nb)
for processes, & this applies to all processes in Linux.
Each process has an ID, a nb that is unique for that process.
*/

#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int id = fork();
    printf("%d\n", getpid());
    return (0);
}

/*
In this case, to get that ID we have to include <sys/wait.h>
- Like always, we first create a child process with the fork() function.
- Then, we call a function (in printf) called getpid => Which gonna get
the process ID for our current process that we're in.
getpid => Return a pid_t which is usually an int, whithout parameters.

- Launch : we should get two IDs.
First one, ID of the child process that was created from fork.
Second one, ID of the parent process that we have launched with our ID.
*/

int main(int argc, char *argv[])
{
    int id = fork();
    printf("Current ID: %d, parent ID: %d\n", 
        getpid(), getppid());
    return (0);
}

/*
In order to get a parent process ID each time a process is called: 
getppid() => Basically the same as the previous one, BUT this one
will return the parent process ID.

Output : 
1. First line : Gonna get the current ID & the parent one.
So the current is XXX, his parent it will be XXX.
2. Second line : Get the current (main process) who has launched
the first current one. And his parent's ID is XXX.


Basically : 
Every process in the system has a parent process ID that has
launched that process execpt the process with ID 0, that is the main
process that launched everything.
*/

int main(int argc, char *argv[])
{
    int id = fork();
    if (id == 0) // 0 if it's the child process.
    {
        sleep(1);
    }
    printf("Current ID: %d, parent ID: %d\n", 
        getpid(), getppid());
    return (0);
}

/*
Usually, the parent process wait for the child process to finish,
bce that's usually how processes should terminate.

What's happening if it's the other way around ?

1. We check if id == 0 (so if it's the child p.)
2. sleep(1);
Instead of doing what the parent p. does, we wait like 1 sec.
What's going to happen ?
Both a timer start at the same time, but since the child p. is
going to wait, the parent p. is gonna terminate.

Output : 
1. First line : Is the IDs for the parent p. 
2. Second line : Then, come after, the IDs of the child p. 
(bigger than the parent p.)
Normally, the parent ID of the child p. is the same as the Current ID
of the parent p. BUT here it's different.
Why ? Bce the parent p. actually terminated while still having the child p.
running, a new parent p. has been assigned to that child p. 

Main idea here : 
We get a different process ID if we terminate the (official) parent p. 
before the child p.
=> It's considered as a zombie process, bce if we try to kill it
with a sink kill command it's not going to free the memory.
=> So, we have wait for child p. to end. 
*/

int main(int argc, char *argv[])
{
    int id = fork();
    if (id == 0) // 0 if it's the child process.
    {
        sleep(1);
    }
    printf("Current ID: %d, parent ID: %d\n", 
        getpid(), getppid());
    if (id != 0) // So, if we are in the parent p. wait.
    {
        wait(NULL);
    }
    return (0);
}

/* 
Need to put NULL as a param. of wait, bce it's a pointer to 
something that tells us what's happened with that process.

We can also call wait() without checking if it's a parent p.
=> Bce if it's not a parent, it's still going to properly finish
the execution.

Output : 
We'll get, first, the parent p. ID and then the children one.
Why ? Bce the wait() function is going to check if there is any
child p. to wait for. If not, it's gonna return a negative nb.
*/

int main(int argc, char *argv[])
{
    int id = fork();
    if (id == 0) // 0 if it's the child process.
    {
        sleep(1);
    }
    printf("Current ID: %d, parent ID: %d\n", 
        getpid(), getppid());
    int res = wait(NULL);
    if (res == -1)
        printf("No children to wait for\n");
    else
        printf("%d finished execution\n", res);
    return (0);
}

/*
If there is no "error" from wait() function we gonna print the ID
when the execution is finished.

Output : 
We still get both conditions (printf), what do we get from the wait() called ?
=> It's the process ID we actually waited for.
So, the parent process said (4179) finished the execution.
This is useful when dealing with multiple child p.

Conclusion : We should actually call the wait() function at the end
of the program if we are forking it anywhere.
*/