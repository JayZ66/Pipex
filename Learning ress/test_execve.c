#include <unistd.h>
#include <stdio.h>

// int main()
// {
//     char *const  args[] = { "ls", NULL }; // the command
//     char *const  envp[] = { NULL }; // env.
//     execve("/usr/bin/ls", args, envp); // execute command at the path.
//     perror("execve");
//     return (1);
// }

int main()
{
    printf("PID before the execve is: %d\n", getpid());
    char *const  args[] = { "ls", NULL }; // the command
    char *const  envp[] = { NULL }; // env.
    execve("/usr/bin/ls", args, envp); // execute command at the path.
    perror("execve");
    printf("PID AFTER the execve is: %d\n", getpid()); // Why is this not getting printed ?
    return (1);
}