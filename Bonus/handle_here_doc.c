/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 09:33:19 by marvin            #+#    #+#             */
/*   Updated: 2024/03/11 09:33:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	child_here_doc(int *pfd, char **argv)
{
	char	*line;

	close(pfd[0]);
	dup2(pfd[1], STDOUT_FILENO);
	close(pfd[1]);
	while (1)
	{
		line = get_next_line(0);
		if (ft_strncmp_limiter(line, argv[2], ft_strlen(argv[2])) == 0)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd(line, 1);
		free(line);
	}
}

void	parent_here_doc(int *pfd, char **argv)
{
	(void)argv;
	close (pfd[1]);
	dup2(pfd[0], STDIN_FILENO);
	close (pfd[0]);
	wait(NULL);
}

void	here_doc(char **argv)
{
	int	pfd[2];
	int	pid;

	if (pipe(pfd) == -1)
	{
		perror("Pb while creating pipe\n");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Pb while creating child\n");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		child_here_doc(pfd, argv);
	else
		parent_here_doc(pfd, argv);
}
