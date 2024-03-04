
/*
In this chapter : See how we communicate between processes
using pipes.
*/

int main(int argc, char *argv[])
{
    int p1[2];
    if (pipe(p1) == -1)
        return (1);
    int pid = fork(); // We fork the p. to get 2 processes.
    if (pid == - 1)
        return (1);
    if (pid == 0) // We know that we are in the child p.
    {
        int x;
        if (read(p1[0], &x, sizeof(x)) == -1) // 3. The child p. is taking over & read the nb.
            return (1);
        printf("Received %d\n", x);
        x *= 4; // 4. Will multiply the nb by 4.
        if (write(p1[1], &x, sizeof(x)) == -1) // 5. Write the nb back & send it into the pipe.
            return (1);
        printf("Wrote %d\n", x);
    }
    else
    {
        srand(time(NULL));
        int y = rand() % 10; // 1. We generate the nb.
        if (write(p1[1], &y, sizeof(y)) == -1) // 2. We are sending it into the pipe.
            return (1);
        printf("Wrote %d\n", y);
        if (read(p1[0], &y, sizeof(y)) == -1); // 6. Here, we should receive back the nb.
            return (1);
        printf("Result is %d\n", y);
        wait(NULL);
    }
    close(p1[0]);
    close(p1[1]);
    return (0);
}

/*
Here we want to take a digit of 5, then send it to the other process.
The other process will multiple this nb by 4, & then the result is send
to the first process in order to print it.
We'll use pipes to communicate between processes.
*/

/*
First, we are in the child p. we want to read the data from the
parent p. who is the one that generates the nb. 

What do we do ? 
1. We should define a variable to get the nb.
2. Then we would need to multiply this x by 4.
3. Then we write in P1[1] the nb multiply by 4 (which is x).

Then, let's do the same thing for the parent p.
1. Let's generate the numbers by using srand().
2. Creating a var. to get the nb generated.
3; Then we write it to the pipe in order to sending it.
So the child p. will take over and read that nb & multiplied it.
4. After, we want to read the result back, so whatever nb we have generated
it should be multiplied by four in the other process.

Output : 
1. We generate the nb with the parent p.
2. The child received it.
3. But then the final result is printed before the child write the
result multiplied by 4.
*/

/*
What's the problem for the end of the output ? Wrong order.

It's just a problem of printing, as the final result (sent by the parent p.)
is right. 
When the child p. is sending the nb multiplied, the parent p. read it from
the pipe and then print the result, before the child p. take over & print
what it wrote.
*/


int main(int argc, char *argv[])
{
    int p1[2];
    if (pipe(p1) == -1)
        return (1);
    int pid = fork(); // We fork the p. to get 2 processes.
    if (pid == - 1)
        return (1);
    if (pid == 0) // We know that we are in the child p.
    {
        int x;
        if (read(p1[0], &x, sizeof(x)) == -1) // 3. The child p. is taking over & read the nb.
            return (1);
        printf("Received %d\n", x);
        x *= 4; // 4. Will multiply the nb by 4.
        if (write(p1[1], &x, sizeof(x)) == -1) // 5. Write the nb back & send it into the pipe.
            return (1);
        printf("Wrote %d\n", x);
    }
    else
    {
        srand(time(NULL));
        int y = rand() % 10; // 1. We generate the nb.
        if (write(p1[1], &y, sizeof(y)) == -1) // 2. We are sending it into the pipe.
            return (1);
        printf("Wrote %d\n", y);
        if (read(p1[0], &y, sizeof(y)) == -1); // 6. Here, we should receive back the nb.
            return (1);
        printf("Result is %d\n", y);
        wait(NULL);
    }
    close(p1[0]);
    close(p1[1]);
    return (0);
}

/*
BUT there is a caveat (mise en garde), if we try to comment out this
printf (between write & read) in the parent p. What's happening ?
OUTPUT : We only get as a result nine, & the prog. didn't finish.
Will not happening each time !

Why ? 
When we do a pipe(), we actually have 4 fd, 2 for the child & 2
for the parent p. They both are opened.
When we write in the pipe, since we have 2 fd, we can't decice who
can read after. 

What's happening here ? 
The nb (9) is generated, then it's written to the pipe & immediatly
after it's read in the same process. So, it's write & read.
The child p. is like okay but what happened, i can't read anything.
It's stuck in the child p. at the read step. bce the parent p. read
it faster than it did.

But when the printf was there, there was a break in between the read
& write, so the child p. had enough time to read it !
Then, the parent p. waits for the child p. to response and multiply
the nb, it read, by 4. And finally, to write it for the parent p.

Conclusion : 
We can't have a pipe that both sends data & receives data on the
same process.
We need two pipe in order to achieve this solution.
*/

int main(int argc, char *argv[])
{
    int p1[2]; // C => P
    int p2[2]; // P => C
    if (pipe(p1) == -1 || pipe(p2) == -1)
        return (1);
    int pid = fork(); // We fork the p. to get 2 processes.
    if (pid == - 1)
        return (1);
    if (pid == 0) // We know that we are in the child p.
    {
        close(p1[0]);
        close(p2[1]);
        int x;
        if (read(p2[0], &x, sizeof(x)) == -1)
        printf("Received %d\n", x);
        x *= 4;
        if (write(p1[1], &x, sizeof(x)) == -1)
            return (1);
        printf("Wrote %d\n", x);
        close(p1[1]);
        close(p2[0]);
    }
    else
    {
        close(p2[0]);
        close(p1[1]);
        srand(time(NULL));
        int y = rand() % 10; // 
        if (write(p2[1], &y, sizeof(y)) == -1) // Parent should write, send data, to the child via p2.
            return (1);
        // printf("Wrote %d\n", y);
        if (read(p1[0], &y, sizeof(y)) == -1); // Parent should read from the child the result.
            return (1);
        printf("Result is %d\n", y);
        close(p1[0]);
        close(p2[1]);
        wait(NULL);
    }
    close(p1[0]);
    close(p1[1]);
    return (0);
}

/*
We'll try to add another pipe to solve this pb.
Let's say that p1[2] is the one that goes from the child to the parent.
And p2[2] is in the other way, from the parent to the child.

To start, we have to first close fd, otherwise we'll have too many.
The first pipe (P1) on the child only write to it.

Child process : 
- So, we don't need to read from the first pipe on the child p., then
we close p1[0].
- Same, with the writing end of the second pipe (P2), we don't need it.
As the child p. never writes anything to it.

We adapt the code : 
- We first, in the child p., want to read using p2. So, we are going
to just swap to p2.
- Then, as we can't use the same pipe to read & write, so we'll write
in p1.

Parent process : We have to close certain ends of the pipe.
- We don't need to read in p2, as we use p1. So, we close p2[0].
- We don't need to write in p1, as we use p2. So, we close p1[1].

Finally, we close the remaining pipes ends once we're done.
This way is guaranteed to always work, because whatever we write
in the parent p., it's done in the second pipe (p2).
And the other way around, like a mirror.
*/