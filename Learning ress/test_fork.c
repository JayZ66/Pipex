
#include <stdio.h>
#include <unistd.h>

// int main()
// {
//     pid_t   pid; // Create a child process using fork();
//     pid = fork();
//     // Parent process.
//     printf("Hello, i am the parent process! My PID is %d, and my child's PID is %d.\n", getpid(), pid);
//     return (0);
// }


int main() 
{
    pid_t pid;

    pid = 9; // Crushed after fork calls.
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");    
    printf("Hello1, I am main process (before fork). My PID is %d.\n", getpid());
    // Create a child process using fork()
    pid = fork();
    printf("------------------------------------\n");     
    printf("Hello1, I am main process (after fork). My PID is %d.\n", getpid());
    if (pid < 0) {
        // Fork failed
        fprintf(stderr, "Fork2 failed.\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Hello1, I am the child process! My PID is %d, and my child's PID is %d\n", getpid(), pid);
    } else {
        // Parent process
        printf("Hello1, I am the parent process! My PID is %d, and my child's PID is %d.\n", getpid(), pid);
    }

    return 0;
}