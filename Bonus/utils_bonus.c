/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:56:45 by marvin            #+#    #+#             */
/*   Updated: 2024/03/11 10:56:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_strncmp_limiter(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	while (i < n && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (i == n && s1[i] == '\n' && s1[i + 1] == '\0')
		return (0);
	else
		return (1);
}

int	open_file(int argc, char **argv, int flag)
{
	int	first_file;
	int	last_file;

	if (flag == 1)
	{
		last_file = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (last_file == -1)
		{
			perror("Can't open last file\n");
			exit(EXIT_FAILURE);
		}
		return (last_file);
	}
	else if (flag == 2)
	{
		last_file = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (last_file == -1)
		{
			perror("Can't open last file\n");
			exit(EXIT_FAILURE);
		}
		return (last_file);
	}
	else if (flag == 0)
	{
		first_file = open(argv[1], O_RDONLY, 0644);
		if (first_file == -1)
		{
			perror("Can't open first file\n");
			exit(EXIT_FAILURE);
		}
		return (first_file);
	}
	return (perror("Can't open file\n"), 1);
}

void	check_args(int argc, int flag)
{
	if (flag == 0)
	{
		if (argc < 5)
		{
			perror("Not enough args.\n");
			exit(EXIT_FAILURE);
		}
	}
	else if (flag == 1)
	{
		if (argc < 6)
		{
			perror("Wrong nb of args\n");
			exit(EXIT_FAILURE);
		}
	}
}
