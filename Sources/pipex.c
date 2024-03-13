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

#include "../pipex.h"

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
		child_process(fd, argv, env);
	else
		parent_process(fd, argv, env);
	return (0);
}
