
/*
In this chapter : We'll see how to use, and why,
fork and pipe. How to deal with multiple processes & threads.

Here, we want to sum all the elements up, but in different manners.
In order to take advantage of multiple processors.
How to do it ? 
By dividing the array into two & leaving half of the array to be
calculated by one of the process, & the other one by the other p.
One process will write that partial sum in the pipe, & the other one 
gonna read it to sum all.
*/

int main(int argc, char *argv[])
{
    int arr[] = {1, 2, 3, 4, 1, 2};
    int arrSize = sizeof(arr) / sizeof(int); // Nb of bytes in the array. & then give us the nb of digit in the array.
    int start;
    int end;
    int fd[2];
    if (pipe(fd) == -1)
        return (1);
    int id = fork();
    if (id == -1)
        return (2);
    if (id == 0) // If we are in the child process.
    {
        start = 0;
        end = arrSize / 2;
    }
    else
    {
        start = arrSize / 2;
        end = arrSize;
    }
    int sum = 0;
    int i;
    for (i = start; i < end; i++;)
        sum+= arr[i];
    printf("Calculated partial sum: %d\n", sum);
}

/*
As we divide the array, we should specify to each process where it has
to start and where it has to end. So, we need 2 indices.

1. Verify if we are in the child process.
Then, we initialize start to 0 & end to start + 3.

But if we have n elements in the array, we need to first get the size of it.

2. Verify if we are in the parent process.
We want that the parent p. start from the middle up till the end.

3. After intializing the indices, we have to sum for each process.
We put the sum of nb in a variable, thx to the nb received from each
process.

4. Print the sum on the screen.
So, we print the sum of the nb, in the array, received by each process.
*/

int main(int argc, char *argv[])
{
    int arr[] = {1, 2, 3, 4, 1, 2};
    int arrSize = sizeof(arr) / sizeof(int); // Nb of bytes in the array. & then give us the nb of digit in the array.
    int start;
    int end;
    int fd[2];
    if (pipe(fd) == -1)
        return (1);
    int id = fork();
    if (id == -1)
        return (2);
    if (id == 0) // If we are in the child process.
    {
        start = 0;
        end = arrSize / 2;
    }
    else
    {
        start = arrSize / 2;
        end = arrSize;
    }
    int sum = 0;
    int i;
    for (i = start; i < end; i++;)
        sum+= arr[i];
    printf("Calculated partial sum: %d\n", sum);
    if (id == 0)
    {
        close(fd[0]);
        if (write(fd[1], &sum, sizeof(sum)) == -1); // Can also use sizeof(int)
            return (1);
        close (fd[1]);
    }
    else
    {
        close(fd[1]);
        int sumFromChild;
        if (read(fd[0], &sumFromChild, sizeof(int)) == - 1)
            return (1);
        close(fd[0]);
        int totalSum = sum + sumFromChild;
        printf("Total sum is equal to: %d\n", totalSum);
        wait(NULL);
    }
    return (0);
}

/*
So, now we need to send one of the partial sums over to the other process.
How to do that ? By using the pipe we have created.

1. We'll check if we are in the child p.
Means that we'll write in the pipe, so close fd[0] & then use the write() function.
We just want to send something and not receiving it here.
2. We'll check if we are in the parent p.
Here it's the contrary, we want to receive data & not sending it.
To read what was sent by the child p., we have to create a var. to get
the data of the child p.
3. Print the total sum of both processes.
Then we create a var. to get sum the total of the child & parent p.
To do these we have to add sum (from parent p.) & sumFromChild that we get from the pipe.
Finally, we CAN'T forget to add the wait() function at the end (in the parent p.),
in order to wait for the child p. to finish is execution, so that it can send his total first.
*/

/*
The main thing here, is when you have a large range of data, you can
process them independently in different processes.
And also distribute them in different ways.
*/
