/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_path_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:30:38 by marvin            #+#    #+#             */
/*   Updated: 2024/03/08 14:30:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	**take_path(char **env)
{
	int		i;
	int		j;
	char	*str;
	char	**path;

	i = -1;
	while (env[++i])
	{
		j = -1;
		while (env[i][++j])
		{
			if (env[i][j] == '=')
			{
				str = ft_substr(env[i], 0, j);
				if (ft_strcmp(str, "PATH") == 0)
				{
					j++;
					path = ft_split(env[i] + j, ':');
					return (free(str), path);
				}
				free(str);
			}
		}
	}
	return (perror("Impossible to get the path\n"), NULL);
}

char	*get_path(char *cmd, char **env)
{
	char	*each_path;
	char	*exec_path;
	char	**path;
	int		i;

	i = 0;
	path = take_path(env);
	if (!path)
	{
		perror("Can't get the right env. variable\n");
		exit(EXIT_FAILURE);
	}
	while (path[i])
	{
		each_path = ft_strjoin(path[i], "/");
		exec_path = ft_strjoin(each_path, cmd);
		free(each_path);
		if (access(exec_path, X_OK) == 0)
			return (free_tab(path), exec_path);
		free(exec_path);
		i++;
	}
	free_tab(path);
	perror("The executable doesn't exist in the repo\n");
	return (NULL);
}
