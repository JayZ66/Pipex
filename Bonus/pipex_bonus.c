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

	first_file = 0;
	last_file = 0;
	cmd_args = 0;
	if (argc < 5)
		return (perror("Not enough args.\n"), 1);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		if (argc < 6)
			return (perror("Wrong nb of args\n"), 1);
		last_file = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (last_file == -1)
			return (perror("Can't open last file\n"), 1);
		cmd_args = 3; // For not taking into account here_doc, limiter & file2
		// handle_here_doc(argv);
	}
	else
	{
		first_file = open(argv[1], O_RDONLY, 0644);
		if (first_file == -1)
			return(perror("Can't open first file\n"), 1);
		last_file = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (last_file == -1)
			return (perror("Can't open last_file\n"), 1);
		cmd_args = 2; // For not taking into account file1 & file2
		dup2(first_file, STDIN_FILENO); // What we're taking to run cmd.  Cela signifie que le contenu du premier fichier sera utilisé comme entrée pour les commandes.
		close(first_file);
	}
	while (cmd_args < argc - 2) // To check.
	{
		create_pipes(argv[cmd_args], env);
		cmd_args++;
	}
	dup2(last_file, STDOUT_FILENO); //Cela signifie que la sortie des commandes sera écrite dans le dernier fichier.
	exec_command(argv[argc - 2], env); // To execute the last cmd. as the output is the file.
	close(last_file);
}

/*
Dans ce contexte, argc - 2 est utilisé pour s'assurer qu'on itère sur 
tous les arguments après la redirection de fichier. 
Si cmd_args est initialisé à 2, cela signifie que les deux premiers 
arguments ont déjà été pris en compte, donc on itère à partir de 
cmd_args + 1, c'est-à-dire le troisième argument. De même, si cmd_args est 
initialisé à 3, on commence à itérer à partir du quatrième argument.
*/

/*
Pourquoi ouvrir et rediriger les deux fichiers maintenant et pas plus tard ?

- Ouvrir et rediriger le premier fichier avant la boucle garantit que 
la première commande a accès au contenu de ce fichier dès le début 
de son exécution.
- Ouvrir et rediriger le dernier fichier à l'extérieur de la boucle 
après la création de tous les pipes garantit que la dernière 
commande peut écrire son résultat dans ce fichier après avoir 
exécuté toutes les commandes intermédiaires et qu'elle dispose 
d'un accès approprié au fichier de sortie.
*/