
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    pid = fork(); // Create a child process
    if (pid == -1)
    {
        perror("fork"); // If fork fails, output the error
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
        // This block is executed by the child process
        printf("This is the child process. (pid: %d)\n", getpid());
    else
        // This block is executed by the parent process
        printf("This is the parent process. (pid: %d)\n", getpid());
        int status;
        waitpid(pid, &status, 0); //protection for zombies process
    return (0);
}

/*
 * Key Concept of fork(2):
 * - fork() is a system call that creates a new process by duplicating the calling process.
 * - The new process, known as the child, is an exact copy of the parent process but has its own unique process ID.
 * - After fork(), both the parent and the child processes continue execution from the fork() call.
 * - fork() returns the child's PID to the parent process and 0 to the child process.
 * - If fork() fails, it returns -1 to the parent.
 * - In this program, the child process prints its identity ("This is the child process.") and its PID,
 *   while the parent process does the same for its own identity and PID.
 * - This demonstrates the simultaneous execution of two processes (parent and child) following a fork.
 */

int main(int argc, char *argv[])
{
    fork();
    printf("Hello world\n");
    return (0);
}
/*
If you do this, it'll print twice "Hello World".
Why ? Because the fork create a child process, which 
is a duplicate of the parent process (so the main),
that will be executing alongside the parent process.
So, everything before the fork, will be executed once,
& after will be executed twice.
*/

int main(int argc, char *argv[])
{
    int id = fork();
    printf("Hello world from id: %d\n", id);
    return (0);
}

/*
if you add a int, it'll return a nb when printed the str.
It'll do it twice, two separate IDs écrits par la fork.
Un du processus principal (parent) et l'autre du processus enfant.
Qui sera d'ailleurs toujours 0, car fork : 
- Clone le processus appelé, crée une copie exacte.
- Retourne -1 pour erreurs, 0 pour le new process + l'ID
du nouveau process (children) vers l'ancien.

S'il retourne un process ID = 0, cela signifie que l'on est dans le child process.
Si ce n'est pas zéro, c'est qu'on est dans le process principal (parent).
*/

int main(int argc, char *argv[])
{
    int id = fork();
    if (id == 0)
    {
        printf("Hello from child process\n");
    }
    else
        printf("Hello from the main process\n");
    return (0);
}

/*
On a 2 différents hello, un du processus enfant et l'un du processus parent.
*/

int main(int argc, char *argv[])
{
    fork();
    fork();
    printf("Hello World\n");
    return (0);
}

/*
Si on appelle 2 fois la fork, cela va afficher 4 fois le message.
Why ? 
- The 1st fork crée un processus enfant, avec le processus parent en parallèle qui s'exécutent.
- Then, on exécute the 2nd fork, le main process crée un nouveau processus enfant,
et le 1er processus enfant (en cours) crée un new processus enfant.

==> On a donc 4 lignes d'exécution en simultané qui arrivent sur la ligne du printf.
Chaque processus écrit donc le message du printf, soit 4 fois.
==> Il faut voir ça avec les puissances, si on met 4 fork, il y aura 16 lignes écrites.
*/

int main(int argc, char *argv[])
{
    int id = fork();
    if (id != 0) // Means that we're in the main process. So, we create a new child process.
    {
        fork();
    }
    printf("Hello World\n");
}
/*
Si l'on souhaite juste créer 3 processus, il faut add une condition.
On check donc si on est sur le processus parent donc si id est != de 0.
Si oui, on peut créer un new processus et pas qu'une fork se fork soi-même une nouvelle fois.
Donc si on est sur le processus parent (main), on peut split une nouvelle fois, sinon non.

Avec ça, on peut donc créer seulement 3 processus car le processus enfant créé,
ne va pas créer un nouvel enfant.
Dans le sens où, si nous sommes dans le main process, on crée un new enfant,
sinon cela signifie que l'on est dans le child process et qu'on ne souhaite pas crée un new child process.
*/

// WHAT DOES FORK() ACTUALLY RETURN ?
/*
The misunderstanding coming first with the var. name 'id', in
which the return value of fork is stored. We thing that's the
current process id, but that's a bit wrong : it doesn't return
the current process id. 
It does return two values, because fork splits the execution of 
a process. So, it has to return 2 values.

What it is returning ?
1. We have the parent process, first.
Inside, we are returning the child process ID. So, the child p.
that has been created after fork() has been called.
We're returning it inside this ID var.
=> It's going to be different than getpid().

2. What happens inside the child process ?
Here, we've an arbitrary nb, that is 0. It's exactly what we're
getting inside this ID var. Thanks to that, we know that we're
in the child p.
But this zero is not the process id that has been assigned to 
that process, just arbitrary nb. 
It's also going to be different than the return value that
we're gonna get with getpid().

*/
