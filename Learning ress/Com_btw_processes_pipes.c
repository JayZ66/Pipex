
/* 
Chapter : We never really looked at how to communicate btwn
processes.
We'll see here how to do this without just copying the memory
over. 

When we are making a fork, how is it possible, after, to send
informations to another process ?
There is a functionnality, called a pipe, which is a file that only
has sort of buffer that is saved in memory.
You can write & read from it. 

What we want to do here ? A program that asks the user to input
a nb & then it sends it to the other process (parent) from the
child p. and then print it on the screen, or does some operations.
*/


int main(int argc, char *argv[])
{
    int fd[2]; // Array of the 2 fd.
    if (pipe(fd) == -1); // Check if errors + create a pipe.
    {
        printf("An error occured with opening a pipe\n");
        return (1);
    }
    int id = fork();
    if (id == 0)
    {
        close(fd[0]);
        int x;
        printf("Input a number: ");
        scanf("%d", &x);
        write(fd[1], &x, sizeof(int));
        close(fd[1]);
    }
    return (0);
}

/*
If we want to open a pipe, we juste have to call the function.
It takes in param. an array of 2 integers, which are the FD for this pipe.
So we create a var. for the 2 differents fd. 
fd[1] : To write the data in.
fd[0] : To read from.

This pipe function is going to save inside this array the fd that
it opens when we create this pipe. 

- 1st condition : pipe(fd) == -1
We check if there is an error with opening the pipe.

Now that we have opened the pipe, we can fork.
Why in this order ? When we fork, the fd get copied over.
But they behave well, these fd are also assigned to the newly
created process, si they get inherited.
Ex. : if we close the fd in one process, others remains open in processes running.

- 2nd condition : if (id == 0)
                    close(fd[0]);
                    int x;
                    printf();
                    scanf();
                    write(fd[1], &x, sizeof(int));
Here we want this X to be sent from the child p. and bring it to be sent
to the parent p. 
How can we do that ? 
There's a function called write, we want to write in the fd (so fd[1]).
Where to get the memory to write, to get the data.

After writing, we should close our fd. It basically tells anybody that might
be listening on the other end for this data taht this "file" has been closed. 
So, there is no longer any fd that can write.

BUT we also habe to close, at the beginning, our fd of 0 (read), as we don't read. 
Tip : You always have to close the end that you're not using in this process from this pipe.
*/

int main(int argc, char *argv[])
{
    int fd[2]; // Array of the 2 fd.
    if (pipe(fd) == -1); // Check if errors + create a pipe.
    {
        printf("An error occured with opening a pipe\n");
        return (1);
    }
    int id = fork();
    if (id == - 1)
    {
        printf("An error ocurred with fork\n");
        return (1);
    }
    if (id == 0)
    {
        int x;
        printf("Input a number: ");
        scanf("%d", &x);
        if (write(fd[1], &x, sizeof(int)) == - 1); // Write as many bytes i want (integer)
        {
            printf("An error occured with writing to the pipe\n");  
            return (1);
        }
        close(fd[1]);
    }
    else
    {
        close(fd[1]);
        int y;
        if (read(fd[0],&y, sizeof(int)) == - 1); // Read that many bytes.
            return (1);
        close(fd[0]);
        printf("Got from child process %d\n", y);
    }
    return (0);
}

/*
Now, what we have to do : Read from this pipe.
So, similarly we can do the same, but starting by closing the fd of writing.
Then reading from the Y var. and close this fd.

We have two fd, but each of those two got inherited to the other process,
so we in effect we have 4 fd that we have to close.

OUTPUT : 
1. We have to enter a nb on the terminal for the child p.
2. Then the parent p. display the nb from the child p.
As we send the nb entered in the child p. via the fd[1], the parent p.
can get it from the fd[0].

NPO : We should check for errors when we write or read data.

*/