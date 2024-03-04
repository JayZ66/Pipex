
/*
In this chapter : Using the pipe to sort of move the output to
the input of the next command (here 'grep').
So, we want to send the result of the first command to the grep
command, that'll use it to give its result after.

==> This is how we can simulate the pipe operator from back in C.
*/

int main(int argc, char *argv[])
{
    int fd[2];
    if (pipe(fd) == -1)
        return (1);
    int pid = fork();
    if (pid == -1)
        return (1);
    if (pid == 0)
    {

    }
    return(0);
}

/*
So, how can we do that ? ping -c 5 google.com | grep rtt
Analysing this command : 
1. Ping > We have the first program
2. Grep > Is the second program
3. The rest is all parameters needed to the execution of these
programs.
4. The pipe : We are opening a pipe that has two ends.
And those, in this case in bash script, are routed in a certain
way.
We know that if we execute the first part of the line command,
it should print something on the terminal (result & data), but
when we use the pipe, it no longer printed out any pings.
It just printed out whatever grep found.
It means that the output of the left-hand side (left prog.) is
actually routed through this pipe.

The standard output of the first prog. (ping) is the "pipe".
So, the ping is writing its stdout, not to the terminal but
to this pipe.

5. But how does grep know that it has to take a look at those lines ? Given by ping.
That's because the standard input of grep, is set to be on this pipe.
As, the standard input was rerouted to be the pipe, it's not gonna
wait for the keyboard input, it's going to accept this output,
which is stdout of this ping.


How to simulate this behavior ? We already how to do theses things.
We know : 
- how to create a pipe
- how to execute every single one of these progs. using the
exec() family of functions.
- how to redirect output or input

With theses infos, we can simulate this line of code inside our
C program.
*/

/*
Explanation of what's happening in the processes : 
1. The main p. will not do anything with it, it's just going
to create the other processes & the pipe, etc. Will wait, & not
executing the grep or the ping command.

=> It'll fork to another process. That is going to execute our ping.
=> There'll have another process to execute the grep command.

So, we'll have in total 3 processes.

2. The way they'll communicate btwn each other, will be through
a pipe that has been created by our main p.
But we'll redirect the input & output properly from the ping p.
to the grap p.
The flow of info is gonna go from ping to grap.  
*/

int main(int argc, char *argv[])
{
    int fd[2];
    if (pipe(fd) == -1) 
        return (1);
    int pid1 = fork();
    if (pid1 == -1)
        return (1);
    if (pid1 == 0) // Child p. 1 for ping.
    {
        dup2(fd[1], STDOUT_FILENO); // Rerouting the standard output of process.
        close(fd[0]);
        close(fd[1]);
        execlp("ping", "ping", "-c", "5", "google.com", NULL);
    }
    int pid2 = fork();
    if (pid2 == -1)
        return (1);
    if (pid2 == 0)
    {
        dup2(fd[0], STDIN_FILENO);
        close(fd[1]);
        close(fd[0]);
        execlp("grep", "grep", "rtt", NULL);
    }
    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return(0);
}

/*
1. We create the processes & check errors.
2. Then we go in the child p. that will execute the ping.
    1. First, we want to reroute the standard output of our
process that starts the ping.
We have to take the standard output from the ping to write to
the pipe, we have to pass in here fd[1], & we have to pass in here
while the standard output.
    2. We, then, have to close fd[0] as we are not reading here.
But also, have to close fd[1] because it remains open even if
we have duplicated it with dup2. This function creates another one,
so we have 2 fd that point to the same pipe, & but we just need one.
    3. We are creating the prog. with the execv() function.
We start with the name of what we want to execute, then the
arguments needed for the ping prog. (path, option to count,
nb of times, the dest. where i want to ping, NULL pointer.)

3. Let's finish with the other process (grep one).
We create another child p. to execute the grep program with
the info the ping prog.
    1. We call dup2() but this time to fd[0] because grep replaces
its standard output with the reading end of the pipe, grep is wainting
to read from that pipe. It means that it should read from the reading
end which is 0. => We're going to replace that with STDIN_FILENO.
    3. The we close the fds, so first the fd[1] & then fd[0], replaced.
    2. We use the exec() function, with first the prog. we want
to execute, then args : the 1st arg. is going to be grep, the 2nd
arg. is the line that we want to find inside our ping, & NULL.

4. We have to wait for our two child processes, so we use waitpid
to specify which process we have to wait for.

5. There is an issue, is that our writer is still open in the 
main p. (fd[0]/[1]).
Because the grep process still waits on that pipe to get input,
it's only until we close that right end that it will finish its
execution.
=> So, we are gonna have to actually close both end of our pipe
in the parent p.


Warning : 
We use waitpid() function to wait for processes, as we have
many children p. we use this function, to say for which process
we want to wait.
*/

/*
The idea is that grep keeps on reading input, whatever pipe you have,
whatever fd you give it, from the standard output which is for it 
is this pipe now. But since it's a pipe, when doest it know when
to stop reading ? It actually happens when all the writers to that
pipe are closed.
But on thing interesting, is that Unix automatically close this
duplicated fd.
*/