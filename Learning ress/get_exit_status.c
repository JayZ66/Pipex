
/*
In this chapter : 
We didn't check if the prog. that we launched
actually succeeded.
So, how do we check that ?
*/

int main(int argc, char *argv[])
{
    int pid = fork();
    if (pid == -1)
        retun(1);
    if (pid == 0)
    {
        int err = execlp("ping", "ping", "-c", "3", "google.com", NULL);
        if (err == -1)
            return (printf("Could not find prog. to execute\n" ,1));
    }
    else
    {
        int wstatus;
        wait(&wstatus);
        if (WIFEXITED(wstatus))
        {
            int statuscode = WEXITSATUS(wstatus);
            if (statuscode == 0)
                printf("Success!\n");
            else
                printf("Failure with status code %d\n", statuscode);
        }
        printf("Some post processing goes here!\n");
    }
    return (0);
}

/*
We have 2 types of errors to check : 
- If the actual ping prog. doesn't exist or is not found.
- If the actual ping is found is executed but give out an error.

How can we do that ?
1. The exec() function will replace the current process, only
if it's successful. So, if it's wrong, it'll not replace the 
code and it continues its execution.
It'll return an integer so we can create a var. to get this return
value & then check it after.

2. What's if the ping (or other) is actually wrong spelled ? 
OUTPUT : Will go in the check error after the exec function.
But it'll go back then in the parent p. & running it.

The answer is in the wait() function. 
We called it with the NULL parameter, but it gives also info about
what happened with the child p. with returning an int.

We have 2 checks to do with the wstatus : 
1. After it finished execution, we have to test if the prog. terminated
on its own. So, there was no external signal.
When you're in the task manager & try to kill the task, it wouldn't
be a normal termination of the pb. 
In Linux, you can do this by sending the sync kill signal, if we
send it to a process it juste terminates the process not normally.

So, we use WIFEXITED(wstatus), if it returns something different
than zero. Otherwise, (like here) means that the program finished
execution normally.

Next step, we actually take the status code that the ping pro. exited.
So, we create a var. which is the return value inside the main or
the value that it exited with using the exit code.

So, if the statuscode is equal to zero, we know that it was a success
in executing the prog.
Otherwise, it means that is a failure.
*/