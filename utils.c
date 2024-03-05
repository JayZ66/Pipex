/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:11:08 by jeza              #+#    #+#             */
/*   Updated: 2024/03/05 11:40:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free (tab[i]);
		i++;
	}
	free (tab);
}

// Open it if it's existing.
// Creatign & open it if it's not existing.
// void  open_file(char *file, int action) // In order to open files.
// {
//    int   fd;

//    //Comment faire si file pas créé ?
//    if (action == 0)
//       fd = open(file, O_RDONLY);
//    if else (action == 1)
//       fd = open(file, O_WRONLY);
// }