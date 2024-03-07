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

#include "pipex.h"

/*
Steps : 
1. On crée un pipe et un process child. avec les vérifs.
2. On crée une fonction qui exécute les commandes.
3. On crée une fonction qui va chercher le path, le vérifier et l'envoyer.
*/

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
		child_process(fd, argv, env); // Params. : fd; argv; env
	else
		parent_process(fd, argv, env);
	return(0);
}