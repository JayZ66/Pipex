/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:04:33 by marvin            #+#    #+#             */
/*   Updated: 2024/03/07 09:04:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "Libft/libft.h"
# include "get_next_line/get_next_line.h"
# include "printf/ft_printf.h"
# include <stdlib.h> // malloc - free - exit
# include <stdio.h> // open - close - read - write
# include <time.h>
# include <errno.h> // perror - strerror
# include <unistd.h> // access - dup2 - execve - fork - pipe - waitpid
# include <sys/wait.h> // Wait
# include <fcntl.h>

void	free_tab(char **tab);
char	**extract_path(char **env);
char	*select_path(char *cmd, char **env);
void	exec_cmd(char *cmd, char **env);
void	child_process(int *pfd, char **argv, char **env);
void	parent_process(int *pfd, char **argv, char **env);