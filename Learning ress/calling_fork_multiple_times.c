
/*
We've seen before how to identify which process is
which if we have just one simple fork.
*/

int main(int argc, char **argv)
{
    int id1 = fork(); // Child p. = 0 & parent p. != 0
    int id2 = fork();
    return (0);
}

/*
What if we have another fork ?
Each process will create a new process, it means that the parent p.
will create a child p. but also the first child p. will create another child.
It'll create a new process from every single existing p.

How to figure out which process is which ? How does the hierarchy of p. works ?
When we fork for the first time, the id1 is equal to the parent ID (so XXX).
At the same time, the id1 of the first children p. will be 0.

So, when we create the second children p. (2nd fork), as it's a copy of the parent p.
(the 1st children), the id1 will still be 0.
Id2, as we assigned it in the child p., it gonna get Id2 to be equal to actually 0.

The parent of the 2nd child (so the 1sr child), instead of getting a 0,
as it's going to also be a parent, so by being a parent is going to have
an Id set, and this Id2 will be actually something like XXX. 

There is a similar situation happening between the main p. (first parent),
and the second children it has created. 

So, the parent p. has an Id1 of XXX, si the 2nd children p. get a copy of Id1,
which is equal to XXX.
What happens with Id2 ? 
Since it's actually a child, the Id2 is equal to 0.
And the parent p. (first one) is getting and id2 equal to XXX.
*/

/*
When creating 2 forks() : 
- The main p. (parent) will only have access to the child (1st) he created,
& the child (2nd) the parent p. created. 
- But it'll not have access to the one created by his child p. (1st), as his
parent is the child of parent p. (main). 

Tip : 
- If you don't have any ID set, then you are certainly the child of 
another child process. 
And that it doesn't have any child p.
- If one of your IDs is set, it means that you are a parent p. and we have
created a process. In details, if the 2nd id it not 0, it means you are a
parent p.
If ID2 (last one) is equal to 0 it means that you are only a child p. with no more
child p. after.
*/

int main(int argc, char **argv)
{
    int id1 = fork(); // Child p. = 0 & parent p. != 0
    int id2 = fork();
    if (id1 == 0)
    {
        if (id2 == 0)
            printf("We are process y\n"); // So the child p. of the child from the parent p.
        else
            printf("We are process x\n"); // A child of the parent p. but with his own child.
    }
    else
    {
        if (id2 == 0)
            printf("We are process z\n"); //If 2nd Id is equal to 0, it's the other child of the parent p.
        else
            printf("We are the parent process\n");  // If Id1 & Id2 are not equal to 0, it's the parent p.
    }
    return (0);
}

/*
- 1st condition : id1 == 0
What we can do Id1 is equal to zero, it means that we are a child of
the parent p. 
- 2nd conditon : id2 == 0
If Id2 is equal to zero, it means that we are the child of that child
process.
- 3rd condition : else
 Means that we are still a child of the parent (main) p. but we are not
 a process that doesn't have any child.
 We actually do have a child process.
- 4th condition : else
                  if (id2 == 0)
If Id1 is not 0, but Id2 is zero that means that we are another leaf (branche)
of that tree. 
- 5th condition : else
Bce by having no Id set to zero, means that we have to have
been created in this instance of a prog.
It means that we are the main (parent) p.
*/

int main(int argc, char **argv)
{
    int id1 = fork(); // Child p. = 0 & parent p. != 0
    int id2 = fork();
    if (id1 == 0)
    {
        if (id2 == 0)
            printf("We are process y\n"); // So the child p. of the child from the parent p.
        else
            printf("We are process x\n"); // A child of the parent p. but with his own child.
    }
    else
    {
        if (id2 == 0)
            printf("We are process z\n"); //If 2nd Id is equal to 0, it's the other child of the parent p.
        else
            printf("We are the parent process\n");  // If Id1 & Id2 are not equal to 0, it's the parent p.
    }
    wait(NULL);
    return (0);
}

/* 
How can we wait for the processes ? 
Putting a wait(NULL) at the end of the conditions : We might think that it'll wait
correctly for the children to finish, but it's wrong.

Why ? 
- The last children (last two created) will return -1 so that's ok.
- The parent/children is fine bce it only has one children, so it's going
to wait for one children and finish executing. 
- The problem is the parent, as it has 2 children, or the wait() function is waiting for
one of them to finish. So, if one of the child is terminate, the parent p. terminates.
+ The rest doesn't necessarily terminates.
*/

#include <errno.h>

int main(int argc, char **argv)
{
    int id1 = fork(); // Child p. = 0 & parent p. != 0
    int id2 = fork();
    if (id1 == 0)
    {
        if (id2 == 0)
            printf("We are process y\n"); // So the child p. of the child from the parent p.
        else
            printf("We are process x\n"); // A child of the parent p. but with his own child.
    }
    else
    {
        if (id2 == 0)
            printf("We are process z\n"); //If 2nd Id is equal to 0, it's the other child of the parent p.
        else
            printf("We are the parent process\n");  // If Id1 & Id2 are not equal to 0, it's the parent p.
    }
    while (wait(NULL) != -1 || errno != ECHILD); // To wait for all processes to finish.
    {
        printf("Waited for a child to finish\n");
    }
    return (0);
}

/* 
So what to do to fix this problem ? 
We should do a loop to check the return (of processus) to the wait function.
NPO : The wait() function will return -1 if there's nothing to wait for.

But to make sure that we got that negative 1 means that we don't have any more
children, bce there are other errors that we could get.

SOLUTION : we have to check that errno (var.) should be different than ECHILD.
It's going to wait, with this loop & conditions, for all the processes that
it should wait for. 

OUTPUT : We should get this sentence printed three times, bce 3 children.
*/