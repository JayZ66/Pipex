/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:02:19 by marvin            #+#    #+#             */
/*   Updated: 2024/03/06 16:02:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

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
