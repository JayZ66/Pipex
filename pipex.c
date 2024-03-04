/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:15:56 by marvin            #+#    #+#             */
/*   Updated: 2024/03/01 12:15:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Check_path : Take the cmd, in param, we want to execute.
// Take, in param, the var. env. to get the path.
// First, we extract the differents path & then we test which
// one is good for the cmd. we want to execute, and then send it.

char    *select_path(char *cmd, char **env)
{
    char    **path;
    char    *each_path;
    char    *exec_path;
    int     i;
    
    i = 0;
    path = extract_path(env);
    while (path[i])
    {
        each_path = ft_strjoin(path[i], "/"); // To free.
        exec_path = ft_strjoin(each_path, cmd);
        if (access(exec_path, X_OK) == 0)
            return (free_tab(path), exec_path);
        i++;
    }
    free_tab(path);
    return(exit(EXIT_FAILURE), NULL);
}

// Will extract the differents path, to check then
// which path is the right one for our cmd. So, we only have the param. env.
char    **extract_path(char **env) // Name for the "PATH" ?
{
    char    *str;
    char    **path;
    int     i;
    int     j;
    
    i = 0;
    while(env[i])
    {
        j = 0;
        while(env[i][j] && env[i][j] != '=') // So, when we are at the '=' we check what's before to see if it's PATH
            j++;
        str = ft_substr(env[i], 0, j);
        if (ft_strncmp("PATH=", str, 5) == 0)
        {
            free(str);
            path = ft_split(env[i] + j, ':');
            // printf("Voici le path: %s\n", path[i]);
            return (path);
        }
        i++;
    }
    free(str);
    return (exit(EXIT_FAILURE), NULL);
}


/*
Will execute any command we ask for.
2. Splits the command into arguments, finds the path of the command,
we send args[0] bce usually the 1st element of the args' list is the cmd to execute.
3. Executes the command with execve()
4. In case of error, prints the error & exits.
*/
void    exec_command(char *cmd, char **env)
{
    char    *path; // To stock & get the right path to execute cmd.
    char    **args; // To stock the arguments of the command.
    
    args = ft_split(cmd, ' '); // We 1st divide the cmds. we asked for.
    path = select_path(args[0], env); // Selecting the path for the cmd we want to execute.
    if (execve(path, args, env) == -1)
    {
        perror("Execution of commands failed\n");
        free_tab(args);
        free(path); // To check ??
        exit(EXIT_FAILURE);
    }
}


// Create a function for the parent p. & one for the child p.
// child (int argc, int fd[2], char **env)
// Will execute the execv() with the first cmd. as it's the 1st to be executed.
void    child_process(char **argv, int *pfd, char **env)
{
    int fd;
    
    close(pfd[0]);
    fd = open("file1", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
        return (perror("Failed to open file1\n"));
    dup2(fd, STDIN_FILENO); // To read what's in the file.
    dup2(pfd[1], STDOUT_FILENO); // Redirect stdout > end written pipe to write the result.
    close(pfd[1]);
    exec_command(argv[2], env);
}
/*
La première redirection assure que le processus enfant lit à partir du 
fichier spécifié plutôt que de l'entrée standard, et la deuxième 
redirection assure que le processus enfant écrit dans le pipe plutôt 
que dans la sortie standard.

No need to use write() function, as the child p. redirected
his stdout to the written pipe end thx to dup2.
*/

void    parent_process(char **argv, int *pfd, char **env)
{ // Will execute the execv() with the last cmd.
    int fd;
    
    close(pfd[1]);
    dup2(pfd[0], STDIN_FILENO);
    fd = open("file2", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
        return (perror("Failed to open file2\n"));
    dup2(fd, STDOUT_FILENO); // To write the result in this file, & not in the terminal.
    close(pfd[0]);
    exec_command(argv[3], env);
    wait(NULL);
}

int main(int argc, char **argv, char **env)
{
    int fd[2];
    int pid;
    (void)argv;
    
    if (argc != 5)
        return (perror("Wrong nb of arguments\n"), 1);
    if (pipe(fd) == -1)
    {
        perror("Pipe creation error\n");
        return (1);
    }
    pid = fork();
    if (pid == -1)
    {
        perror("Fork creation error\n");
        return (1);
    }
    if (pid == 0) // Child process.
    {
        child_process(argv, fd, env);
    }
    else // Parent process.
    {
        parent_process(argv, fd, env);
    }
    return (0);
}

/*
ENV : 3ème arg. (char **env) => Il faut quand même envoyer argc, argv en param.
Lire jusqu'à path with tab. de tab.
Quand on trouve path, on va jusqu'à '=' et ensuite on fait un split
pour spliter chaque path et utiliser la fonction access() pour tester chaque chemin
pour les commandes et voir où elle se trouve (danns quel path) : OK/KO

=> Il faut avant d'envoyer dans la fonction execve() le path, faire la recherche
dans le tab. et ensuite une fois le bon path trouvé, l'envoyer.
*/

