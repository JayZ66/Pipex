
/*
In this chapter : 
We could just execute any prog. giving its path (var. envt.), its
argument, &, if we wanted, envt var. ourselves.
We want, here, to call a simple ping.

There is a warning here, whenever you would execute taht exact
function, our program would like to stop executing, but our process 
would be replaced with whatever we have called !
*/

int main(int argc, char *argv[])
{
    execlp("ping", "ping", "-c", "3", "google.com", NULL);
    return (0);
}

/*
execlp : 
1. I want a list of arguments to pass in, with the pass environment var.
We want here to call a simple ping.
Arguments : 
First arg, should be the ping.
Then, we want to ping to google.com
Last one, should be NULL. As we don't want this ping to go forever.
We limit the nb of counts, so we pass in another set of args.
With -c & the nb, we tell it how many times it should ping google.com

Output : We should be able to see ping google.com 3 times.
*/

int main(int argc, char *argv[])
{
    execlp("ping", "ping", "-c", "3", "google.com", NULL);
    printf("Success!\n");
    return (0);
}

/*
If we want to print here "success".
OUTPUT : We get the ping but we don't get the printf message.

Why ? Exec() functions replace our whole process, so all the memory
is going to be replaced by its own memory. 
The executin line is goign to be replaced by its own line.

So, after this function, we are done.

This is a big caveat but we know how to create new processes, to fork them.
*/

int main(int argc, char *argv[])
{
    int pid = fork();
    if (pid == -1)
        retun(1);
    if (pid == 0)
    {
        execlp("ping", "ping", "-c", "3", "google.com", NULL);
    }
    else
    {
        wait(NULL);
        printf("Success!\n");
        printf("Some post processing goes here!\n");
    }
    return (0);
}

/*
The main idea is to first fork.
After that, we should habe 2 processes executing the same line of code.
We have a parent & a child, so it's important which one we choose to
execute the exec() function, because with processes it's important to 
wait for the child p. 

But if we call exec on the parent p., it gets replaced and it can no
longer wait for the child p.
So, we cannot call exec on the parent p. bce the child p. will become
a zombie p.

How to do it ?
We should call exec() on our child p. & inside the parent p. we
have to wait for this process to finish.

1. We check if we are in the child p. & then do the exev(), but after
we cannot do anything as it'll get replaced. So we no longer have a
child p. that we can program.
2. But then we have the parent p. that still executes code.
So, we wait for the child p. to finish with the wait function.
And print whatever we want.

OUTPUT : We have the 3 ping and then we print, as the parent p. waited
for the child p. to finish (so executing the execv function). Then, it
get back the right to "run".
*/