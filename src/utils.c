/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:05:49 by marvin            #+#    #+#             */
/*   Updated: 2024/02/15 11:28:52 by lauger           ###   ########.fr       */
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

void free_commands(t_pipex *pipex, int size)
{
	int i;
	int j;

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

void free_all(t_pipex *pipex)
{
	if (pipex != NULL)
	{
		if (pipex->paths != NULL)
			ft_free_tab_size(pipex->paths, pipex->nb_elems);
		if (pipex->cmds != NULL)
			free_commands(pipex, pipex->nb_elems);
	}
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

static char	*find_command_in_directory(const char *cmd, const char *directory)
{
	size_t	command_path_len;
	char	*command_path;

	command_path_len = ft_strlen(directory) + ft_strlen(cmd) + 2;
	command_path = ft_calloc(sizeof(char), command_path_len);
	if (!command_path)
		return (NULL);
	ft_strcat(command_path, directory);
	ft_strcat(command_path, "/");
	ft_strcat(command_path, cmd);
	return (command_path);
}

char	*check_command_existence(const char *cmd, char *env[])
{
	char	*path;
	char	*result;
	char	*command_path;
	char	**directories;
	int		i;

	path = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = ft_substr(env[i], 5, ft_strlen(env[i]) - 4);
			if (!path)
				return NULL;
			break;
		}
		i++;
	}
	if (path == NULL)
		return (NULL);
	directories = ft_split(path, ':');
	free(path);
	if (!directories)
		return (NULL);
	result = NULL;
	i = 0;
	while (directories[i] != NULL)
	{
		command_path = find_command_in_directory(cmd, directories[i]);
		if (!command_path)
		{
			i++;
		}
		else if (access(command_path, F_OK) == 0)
		{
			result = command_path;
			break;
		}
		else
		{
			free(command_path);
			i++;
		}
	}
	ft_free_tab(directories);
	return (result);
}
