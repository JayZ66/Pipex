
#include <unistd.h>
#include <stdio.h>

// int main()
// {
//     int     pfd[2]; // Tab. d'entiers de taille 2. Après l'appel à pipe(), pfd[0] sera le fd pour 
//     // la lecture du pipe & pfd[1] sera le fd pour l'écriture dans le pipe.
//     char    str[20];

//     pipe(pfd); // Crée un new pipe.
//     write(pfd[1], "hello", 5); // Write data (hello) in the fd.
//     read(pfd[0], str, 5); // Read until 2 octets from the fd (pfd[0]), et stocke dans str.
//     str[6] = '\0';
//     printf("%s\n", str); // Display the str content.
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/wait.h>
// #include <string.h>

// int main(void)
// {
//  pid_t   pid;
//  int pfd[2];

//  pipe(pfd);
//  pid = fork();
//  if (pid < 0) 
//  {
//   fprintf(stderr, "Fork2 failed.\n");
//   return 1;
//  }
//  else if (pid == 0)
//  {
//   close(pfd[0]); //close unused end (the reading end) of the pipe
//   write(pfd[1], "this is a new message", 22);  
//   close(pfd[1]); //close after writing into the pipe
//         exit(EXIT_SUCCESS);     
//  }
//  else 
//  {
//   close(pfd[1]); //close unused end (the writing end) of the pipe
//   char  str[22];
//   read(pfd[0], str, 22);
//   printf("Parent received:%s\n", str);
//   close(pfd[0]); //close after reading from the pipe
//   wait(NULL);
//  }
//  return EXIT_SUCCESS;
// }

int main()
{
    int pfd[2]; // 1 to write & 0 to read.
    char str[20]; // To store our string.

    pipe(pfd);
    write(pfd[1], "Bonjour pipe", 13);
    read(pfd[0], str, 13);
    str[13] = '\0';
    printf("La phrase est : %s\n", str);
    return (0);
}