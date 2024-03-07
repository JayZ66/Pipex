/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:02:32 by marvin            #+#    #+#             */
/*   Updated: 2024/03/07 09:02:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "pipex_bonus.h"

// While argv[after file] et argv[avant file2]
// Tu pipe !

char	**extract_path(char **env)
{
	int	i;
	int	j;
	char	*str;
	char	**path;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j])
		{
			if (env[i][j] == '=')
			{
				str = ft_substr(env[i], 0, j); // Take the beginning of each str in env.
				if (ft_strcmp(str, "PATH") == 0)
				{
					j++;
					free(str);
					path = ft_split(env[i] + j, ':');
					return (path);
				}
			}
			j++;
		}
		free(str);
		i++;
	}
	perror("Impossible to get the path\n");
	return (NULL);
}

// char	**extract_path(char **env)
// {
// 	int	i;
// 	int	j;
// 	char	*str;
// 	char	**path;

// 	i = 0;
// 	while (env[i])
// 	{
// 		j = 0;
// 		while (env[i][j] && env[i][j] != '=')
// 			j++;
// 		str = ft_substr(env[i], 0, j); // Take the beginning of each str in env.
// 		if (ft_strcmp(str, "PATH") == 0)
// 		{
// 			j++;
// 			free(str);
// 			path = ft_split(env[i] + j, ':');
// 			return (path);
// 		}
// 		free(str);
// 		i++;
// 	}
// 	perror("Impossible to get the path\n");
// 	return (NULL);
// }

char	*select_path(char *cmd,char **env)
{
	char	*each_path;
	char	*exec_path;
	char	**path;
	int		i;

	i = 0;
	path = extract_path(env);
	if (!path)
	 {
		perror("Can't get the right env. variable\n");
		exit(EXIT_FAILURE);
	 }
	while (path[i])
	{
		each_path = ft_strjoin(path[i], "/");
		exec_path = ft_strjoin(each_path, cmd); // In order to add the cmd.
		free(each_path);
		if (access(exec_path, X_OK) == 0) // Check if the executable exists in the repo.
			return(free_tab(path), exec_path);
		free(exec_path);
		i++;
	}
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
	{
		perror("Failed to split cmd\n");
		exit(EXIT_FAILURE);
	}
	path = select_path(args[0], env);
	if (!path)
	{
		free_tab(args);
		perror("Didn't get the path\n");
		exit(EXIT_FAILURE);
	}
	if (execve(path, args, env) == -1)
	{
		perror("Cmd not executed\n");
		free_tab(args);
		free(path);
		exit(EXIT_FAILURE);
	}
}

void	child_process(int *pfd, char **argv, char **env)
{
	int	fd;

	close (pfd[0]);
	fd = open(argv[1], O_RDONLY, 0777); // To check
	if (fd == -1)
		return(perror("Problem with opening the file\n"));
	dup2(fd, STDIN_FILENO);
	dup2(pfd[1], STDOUT_FILENO);
	close(pfd[1]);
	exec_cmd(argv[2], env); // Param. : cmd (argv[2])
	close(fd);
}

void	parent_process(int *pfd, char **argv, char **env)
{
	int	fd;

	close (pfd[1]);
	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Problem with opening/creating file2\n");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	dup2(pfd[0], STDIN_FILENO);
	close(pfd[0]);
	exec_cmd(argv[3], env); // Param.: cmd (argv[3])
	close(fd);
	wait(NULL);
}

int	main(int argc, char **argv, char **env)
{
	int	fd[2];
	int	pid;

	if (argc != 5)
		return (perror("Problems of args\n"), 1);
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