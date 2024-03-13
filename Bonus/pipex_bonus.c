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

#include "../pipex.h"

int	main(int argc, char **argv, char **env)
{
	int	cmd_args;
	int	last_file;
	int	first_file;

	check_args(argc, 0);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		check_args(argc, 1);
		last_file = open_file(argc, argv, 2);
		cmd_args = 3;
		here_doc(argv);
	}
	else
	{
		first_file = open_file(argc, argv, 0);
		last_file = open_file(argc, argv, 1);
		cmd_args = 2;
		dup2(first_file, STDIN_FILENO);
		close(first_file);
	}
	while (cmd_args < argc - 2)
		create_pipes(argv[cmd_args++], env);
	dup2(last_file, STDOUT_FILENO);
	exec_command(argv[argc - 2], env);
	close(last_file);
}
