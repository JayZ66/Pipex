/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:28:59 by marvin            #+#    #+#             */
/*   Updated: 2024/03/08 14:28:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	child_process_b(int *pfd, char *cmd, char **env)
{
	(void)cmd;
	(void)env;
	close(pfd[0]);
	dup2(pfd[1], STDOUT_FILENO); // Each time we want to send the output of the cmd to the STDOUT.
	close(pfd[1]); // In order to send this data to the next cmd. from the pipe.
	exec_command(cmd, env);
}

void	parent_process_b(int *pfd, char *cmd, char **env)
{
	(void)cmd;
	(void)env;
	close(pfd[1]);
	dup2(pfd[0], STDIN_FILENO); // When we execute a cmd. we read the data from the end of this pipe.
	close(pfd[0]);
	wait(NULL);
}