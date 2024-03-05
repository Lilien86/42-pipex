/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:41:47 by lauger            #+#    #+#             */
/*   Updated: 2024/03/01 11:10:51 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_tab_size(char **str, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (str[i] != NULL)
			free(str[i]);
		i++;
	}
	free(str);
}

void	free_commands(t_pipex *pipex, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		if (pipex->cmds[i] != NULL)
		{
			j = 0;
			while (pipex->cmds[i][j] != NULL)
			{
				free(pipex->cmds[i][j]);
				j++;
			}
			free(pipex->cmds[i]);
		}
		i++;
	}
	free(pipex->cmds);
}

void	free_all(t_pipex *pipex)
{
	if (pipex != NULL)
	{
		if (pipex->paths != NULL)
			ft_free_tab_size(pipex->paths, pipex->nb_elems);
		if (pipex->cmds != NULL)
			free_commands(pipex, pipex->nb_elems);
	}
	if (pipex)
		free(pipex);
}

int	is_path(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '/' || s[i] == '.' || s[i] == '~')
			return (1);
		i++;
	}
	return (0);
}
