/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:56:42 by marvin            #+#    #+#             */
/*   Updated: 2024/03/01 10:56:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "Libft/libft.h"
# include "get_next_line/get_next_line.h"
# include "printf/ft_printf.h"
# include <stdio.h> // open - close - read - write
# include <time.h>
# include <errno.h> // perror - strerror
# include <stdlib.h> // malloc - free - exit
# include <unistd.h> // access - dup2 - execve - fork - pipe - waitpid
# include <sys/wait.h> // Wait
# include <fcntl.h>

char	*select_path(char *cmd, char **env);
char	**extract_path(char **env);
void	exec_command(char *cmd, char **env);
void	child_process(char **argv, int *pfd, char **env);
void	parent_process(char **argv, int *pfd, char **env);
void	free_tab(char **tab);

#endif