
/*
In this chapter : We'll send a string that we have read from the
user, from the child p. to the parent p.
And the parent p. will just show that string on the terminal.
*/
// Not 2 pipes because any process has to read AND write.
int main(int argc, char *argv[])
{
    int fd[2];
    if (pipe(fd) == -1) // Opening the pipe.
        return (1);
    int pid = fork(); // To get 2 processes.
    if (pid == -1)
        return (1);
    if (pid == 0) // If we are in the child p.
    {
        close (fd[0]); // We don't need to read in the child p.
        char    str[200];
        printf("Input string: ");
        fgets(str, 200, stdin); // We want to read the input from the keyb. of the user. (terminal)
        str[strlen(str) - 1] = '\0' // Going at the end of the str. to put NULL terminator.
        int n = strlen(str) + 1; // The nb of characters.
        if (write(fd[1], &n, sizeof(int)) < 0) // Take the add. of the var. to access the value.
            return (1); // We just put size of int bce we already get the size.
        if (write(fd[1], str, sizeof(char) * n) < 0)
            return (1);
        close (fd[1]);
    }
    else
    {
        close (fd[1]);
        char    str[200];
        if (read(fd[0], &n, sizeof(int)) < 0)
            return (1);
        if (read(fd[0], str, sizeof(char) * n) < 0)
            return (1);
        printf("The string received: %s\n", str);
        close(fd[0]);
        wait(NULL);
    }

    return(0);
}

/*
First, if we are in the child p. we want to read a str from the
user and then send it over through the pipe to the parent p.

How to do that ? 
1. First, let's read that line of text. 
We use the function fgets(), it takes in first a string that you
want to read into. So, in this case, we want to read into str,
we put the max characters that it can fit in. Finally, the stream
it should read from.
2. We have to remove the \n, at the end of the str, as it stays at the end.
3. We did the reading part, so now we'll send that string to the
parent p. How can we do it ? 
4. We'll write this string in the pipe, to send it. To calculate
the size we'll use strlen, to give the right space in the pipe.
+ 1 for the NULL character.

5. Then, we go in the parent p. to get this str from the child p.
6. We start, by closing the pipe end fd[1] as we'll not write.
7. We'll declare a str, as we're in a different process, to receive
the str from the child p.
8. Then, we want to read from the pipe with fd[0], but how can we
get the size of the str without the str ? 
So, we must first send the nb of charachters through the pipe,
from child p.
To do that, we need a reference to send it, so a var.
We give the size to this var., then we send the add. of the var.
in the pipe.
9. So, the parent p. read it by having the add. of the var. & getting
the nb of characters sent.
10. And finally, read what's in the str, with the right size, as
we have a sizeof(char) * n, which is the nb of characters that we
got just before.

Other way : 
We can also read the str by creating a loop, & reading one character
at a time to put it in a var. until we get to the '\0' => But not efficient.
*/