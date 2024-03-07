/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:30:11 by marvin            #+#    #+#             */
/*   Updated: 2024/03/06 15:30:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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