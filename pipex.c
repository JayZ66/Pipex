/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipexbis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:42:35 by marvin            #+#    #+#             */
/*   Updated: 2024/03/05 11:42:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
Steps : 
1. On crée un pipe et un process child. avec les vérifs.
2. On crée une fonction qui exécute les commandes.
3. On crée une fonction qui va chercher le path, le vérifier et l'envoyer.
*/

char	**take_path(char **env)
{
	int	i;
	int	j;
	char	*str;
	char	**path;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		str = ft_substr(env[i], 0, j); // Take the beginning of each str in env.
		if (ft_strncmp("PATH", str, 4) == 0)
		{
			// free(str);
			j++;
			path = ft_split(env[i] + j, ':');
			return (path);
		}
		i++;
	}
	perror("Impossible to get the path\n");
	// free(str);
	return (NULL);
}

char	*check_path(char *cmd,char **env)
{
	char	*each_path;
	char	*exec_path;
	char	**path;
	int		i;

	i = 0;
	path = take_path(env);
	while (path[i])
	{
		each_path = ft_strjoin(path[i], "/");
		exec_path = ft_strjoin(each_path, cmd); // In order to add the cmd.
		// printf("La ligne : %s\n", exec_path);
		if (access(exec_path, X_OK) == 0) // Check if the executable exists in the repo.
		{
			free(each_path);
			// free_tab(path);
			// printf("path : %s\n", exec_path);
			return(exec_path);
		}
		i++;
	}
	free(each_path);
	free(exec_path);
	free_tab(path);
	perror("The executable doesn't exist in the repo\n");
	return (NULL);
}

void	exec_cmd(char *cmd, char **env)
{
	char	*path;
	char	**args;

	args = ft_split(cmd, ' '); // To get the cmd without flags.
	if (!args)
		return (perror("Split didn't worked\n"));
	path = check_path(args[0], env);
	// printf("%s\n", path);
	if (execve(path, args, env) == -1)
	{
		perror("Cmd not executed\n");
		free_tab(args);
		free(path);
		exit(EXIT_FAILURE);
	}
	// free_tab(args);
	// free(path); // To check !
	return ;
}

void	child_process(int *pfd, char **argv, char **env)
{
	int	fd;

	fd = open("file1", O_RDONLY, 0644); // To check
	if (fd == -1)
		return(perror("Problem with opening the file\n"));
	close(pfd[0]);
	dup2(pfd[1], STDOUT_FILENO);
	dup2(fd, STDIN_FILENO);
	close(pfd[1]);
	exec_cmd(argv[2], env); // Param. : cmd (argv[2])
}

void	parent_process(int *pfd, char **argv, char **env)
{
	int	fd;

	fd = open("file2", O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
		return(perror("Problem with opening/creating file2\n"));
	close(pfd[1]);
	dup2(pfd[0], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	exec_cmd(argv[3], env); // Param.: cmd (argv[3])
	close(pfd[0]);
	wait(NULL);
}

int	main(int argc, char **argv, char **env)
{
	int	fd[2];
	int	pid;

	// if (argc != 5)
	// 	return (perror("Problems of args\n"), 1);
	// printf("argv[2] : %s\n", argv[2]);
	// printf("argv[3] : %s\n", argv[3]);
	(void)argc;
	if (pipe(fd) == -1)
		return (perror("Problem with the pipe"), 1);
	pid = fork();
	if (pid == -1)
		return (perror("Problem with the fork"), 1);
	if (pid == 0)
		child_process(fd, argv, env); // Params. : fd; argv; env
	else
		parent_process(fd, argv, env);
	return(0);
}