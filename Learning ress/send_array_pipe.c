
/*
In this chapter : Exercices for using pipe.
*/


// First, we want to create 2 processes
// 1. Child p. should generates random nb & send them to the parent.
// 2. Parent is going to sum all the nb & print the result.
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
        close(fd[0]);
        int n;
        int i;
        int arr[10]; 
        srand(time(NULL));
        n = rand() % 10 + 1; // Generate that amount of nb.
        printf("Generated: ");
        for (i = 0; i < n; i++)
        {
            arr[i] = rand() % 11; // So we can get nb between 0 & 10.
            printf("%d ", arr[i]);
        }
        printf("\n");
        if (write(fd[1], &n, sizeof(int)) < 0)
            return(1);
        printf("Sent n = %d\n", n);
        if (write(fd[1], arr, sizeof(int) * n) < 0);
            return (1);
        printf("Sent array\n");
        close (fd[1]); // We close the pipe end after writing.
    }
    else
    {
        close(fd[1]);
        int n;
        int i;
        int sum = 0;
        int arr[10];
        if (read(fd[0], &n, sizeof(int)) < 0)
            return(1);
        printf("Received n = %d\n", n);
        if (read(fd[0], arr, sizeof(int) * n) < 0);
            return (1);
        printf("Received array\n");
        close (fd[0]); // We close the pipe end after reading.
        for (i = 0; i < n; i++)
            sum += arr[i];
        printf("Result is: %d\n", sum);
        wait(NULL);
    }
    return (0);
}

/*
1. First step : Creating a fork of the main p.
2. We check if we are in the child p. and then generate those nb.
    1. Creating a var. that gives us the nb of elements nb to generate.
    2. Creating an array of ten
    2. Using the function srand() that generates random nb.
    3. Generated the amount of nb, so we can get at least 1 nb &
    at most 10 nb.
    4. Creating a loop to fill the array with the nb randomly
    generated, that can be between 0 & 10 (included : %11).

Now, can we send the data ? We need a pipe.
1. We create the pipe & verify errors.
2. We need to choose which process is going to write & read.
As we wrote it before, the child p. should write & the parent p.
should read what's child sent.
    1. We close, in the child p., the read fd.
    2. We close, in the parent p., the write fd.
3. We write the content of the array in the pipe.
4. We go in the parent p.
    1. We close the fd[1] as we want to read from the child.
    2. We create an array of 10, as we are going to receive up to 10 nb.
    3. Then, we read in the arr. the pb is that we don't know what
size we'll read. So how to know it ? We should write first, in the child p.
to send the size of the array to the parent.
    4. Now, that we have sent this to the parent p., we should read
in the parent p. before reading what's in the arr.
Now that we can get the size of the arr. to read, we get it through n var.
& then put as a size "n".
    5. After reading, we close the pipe as we'll
    6. Then we are making a loop in order to get the nb in the array,
    & to do a sum, that we'll display right after.
    7. We don't forget to use the wait() function in order to make sure
    that, even if the child p. takes longer we'll wait for him to finish.

NPO : We always have to send the number of elements in the array, 
before sending it to the parent p.

*/