/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:30:02 by marvin            #+#    #+#             */
/*   Updated: 2024/03/08 14:30:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_command(char *cmd, char **env)
{
	char	*path;
	char	**args;

	args = ft_split(cmd, ' '); // To get the cmd without flags.
	if (!args)
	{
		perror("Failed to split cmd\n");
		exit(EXIT_FAILURE);
	}
	path = get_path(args[0], env);
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

// This function will create as many pipes as necessary,
// depending on the nb of commands.
// The child p. executes the cmd & the parent p. 
// sets up data collection for the next step.
void	create_pipes(char *cmd, char **env)
{
	int	pid;
	int	fd[2];

	if (pipe(fd) == -1)
	{
		perror("Pipe creation failed\n");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Process creation failed\n");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		child_process_b(fd, cmd, env);
	else
		parent_process_b(fd, cmd, env);
}