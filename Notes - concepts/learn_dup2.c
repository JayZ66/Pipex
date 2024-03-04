

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;

    // Open a file called "example.txt" for writing & if not existing we create it.
    fd = open("example.txt", O_WRONLY | O_CREAT, 0644);

    // Redirect stdout to the file descriptor returned by open
    dup2(fd, STDOUT_FILENO);

    // Close the original file descriptor
    close(fd);

    // Output now goes to "example.txt"
    printf("This is printed in example.txt!\n");

    return (0);
}

/*
 * This program demonstrates using dup2(2) for file descriptor redirection.
 * - open() is called to create or open "example.txt" for writing.
 * - dup2() then duplicates this file descriptor to stdout (file descriptor 1).
 * - As a result, any output normally written to stdout, like with printf(),
 *   is now written to "example.txt".
 */

/*
In this chapter :  We are going to see how to not print part
of what's printed by the prog. (Details of the ping operation).

We just want to know if we were able to ping to that website/
*/

int main(int argc, char *argv[])
{
    int pid = fork();
    if (pid == -1)
        return(1);
    if (pid == 0)
    {
        int file = open("pingResults.txt", O_WRONLY | O_CREAT, 0777);
        if (file == -1)
            return (1);
        int file2 = dup2(file, 1);

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
We want to just output all the data into another file.
We want these data to be in a file separate of everything else.
How to do that ? 
1. Let's create a file and open it.
So we put the name of the file, the action so here write & another
option to create the file if it doesn't exist.
Finally, we put the permission of access.

So then, we could start writing into it. 

2. So, now we have the file but how do we say that we want the output
of this ping program to go to our file ping result.

What's a FD ? It's a unique nb across a process.
These represent a key or handle to an input or output ressource.
That could be a file, the terminal input/output, standard output, a pipe, etc.

So, each time you open a process, it will opens certain FD automatically.
Example : 
- The Fd 0 is linked and open to handle STDIN.
- Fd 1 is linked to the STDOUT.
- Fd 2 is linked to the STDERR
When we open a file, it got a fd (here "pingResults.txt")

If we want to replace that 1, of pointing to STDOUT to our file.
==> We can do it thanks to the dupe() function.

So, to do that we create a var. to get the result of the dupe().
It'll returned another fd with another (new) id. that points
to our file pingResults.txt
It's possible then to use these 2 fd that point to the same file,
to do different things in the file.

This function, by itslef, is not that useful but we can use another one.
=> dup2(file, fd)
fd : We want to duplicate.
value : we want the new fd have.
Example : dup2(file, 1);
So the fd will close this stream (stdout) and then open it again
to our ping results.

When we do that before our execv() function, it means that it'll
change it inside the ping program. 
So, when it'll want to write something, it'll not do it on STDOUT
but on our file. 
*/

int main(int argc, char *argv[])
{
    int pid = fork();
    if (pid == -1)
        return(1);
    if (pid == 0)
    {
        int file = open("pingResults.txt", O_WRONLY | O_CREAT, 0777);
        if (file == -1)
            return (1);
        dup2(file, STDOUT_FILENO);
        close(file);
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
Instead of 1 we can change this to a constant STDOUT_FILENO

The fd of the file that we opened before is unused, so we should
close it.
So we can close our var. "file" that we created at the beginning.

But we also don't really need of "file2" because we know it's 1.
So we can just remove the var. file2.
*/