

#include <unistd.h>
#include <stdio.h>

int main()
{
    char *args[3];

    args[0] = "ls";    // Command to execute
    args[1] = "-l";    // Argument: detailed listing
    args[2] = NULL;    // Array must be NULL-terminated

    // Call execve to execute /bin/ls with the specified arguments
    execve("/bin/ls", args, NULL);

    // The following line will not be executed if execve is successful
    printf("This line will not be executed.\n");

    return (0);
}

/*
 * execve() is a system call used to execute a new program, replacing the current process image.
 * - The first argument is the path to the executable ("/bin/ls" in this case).
 * - The second argument is an array of strings (args) that represent the command line arguments.
 * - The third argument is for environment variables, set to NULL in this example.
 * - Upon successful execution of execve, the current process is replaced by the new program,
 *   so any code following execve will not be executed unless execve fails.
 * - The args array includes the command and its arguments, followed by a NULL pointer as the last element.
 * - So the goal is to use execve in a child process.
 */


/*
In this chapter : We'll see how to execute other programs
inside our program.
To do this we have to use the exect() family of functions.
*/

#include <process.h> // Not for Unix systems.

int main(int argc, char *argv[])
{
    _execl("C:\\Windows\\System32\\ping.exe", "C:\\Windows\\System32\\ping.exe",
        "google.com",  NULL);
    printf("Ping finished executing\n");
    return (0);
}

/*
To start we have to call the function _execl().
=> L stands for a list of arg., so we executed the ping prog.
with a list of args.
=> Its taking a file name to an executable & execute that executable
with sort an argument.
Parameters : 
1. file name, we have to pass the file path.
This is going to execute the ping.exe program.
2. The actual arguments that are gonna go to the prog. (so ping). 
Again the path.
These are argv, that we have to pass in.
The args. have a specific format to them, so the first arg. it's
always going to be the path that we have executed.
So, we put this path a second time.
3. Then, it's gonna be the first arg. to our program which is, 
here, "google.com". => The actual args. for the prog.
4. If we don't have anymore args. to pass to this prog. for trying
to launch, we have to pass a NULL pointer.

NPO : The exec() functions take the new ping process (here) and put it on top
of it, so it basically overwriting everything that we had before (memory, execution order).
*/

int main(int argc, char *argv[])
{
    _execlp("ping", "ping",
        "google.com",  NULL);
    printf("Ping finished executing\n");
    return (0);
}

/*
If we want to put ping, in param. like in the command prompt, we can but
we have to use another exev function with a p (execlp).
Why ? Tells the exact function to use the path var. 
The path var. is the one that's loaded auto in the command prompt, that
find in our directors that we have added there, & this pring prog is
in there & it's found.
The P adds that path to our executing space.
*/

int main(int argc, char *argv[])
{
    char *arr[] =   {"ping", "google.com", NULL}; 
    _execvp("ping", arr);
    printf("Ping finished executing\n");
    return (0);
}

/*
The execvp() => (Vectors) Instead of passing in arg. 
we need an array of strings.

Then, we pass in our function execvp() the "ping" arg. &
then the array with our different param.
*/

int main(int argc, char *argv[])
{
    char    *arr[] =   {"ping", "google.com", NULL}; 
    char    *env[] = {"TEST=environment variable", NULL}
    _execvpe("ping", arr, env);
    printf("Ping finished executing\n");
    return (0);
}

/*
The "e" means environment, we can pass in an envt. 
What does that mean ? 
That's a set of variables that we can pass to this through
another array.
1. So, we're going to define our own envt.
2. Then we pass it into our exec() function.

This array is exactly the same as the var. envp[].
*/

int main(int argc, char *argv[])
{
    char    *arr[] =   {"pingr", "google.com", NULL}; 
    char    *env[] = {"TEST=environment variable", NULL}
    _execvpe("ping", arr, env);
    int err = errno;
    printf("Ping finished executing\n");
    return (0);
}

/*
If our code, actually goes & executes the printf line.
It means, that our exec() function failed to run. 
What did it failed ? That's through the errno variable.
If we check what's errno() returns, we see here that's 2.
It means (ENOENT) that there wasn't a file with that name or
no path.
*/

