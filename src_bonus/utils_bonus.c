/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:05:49 by marvin            #+#    #+#             */
/*   Updated: 2024/03/05 10:40:04 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

static char	*check_command_existence_two(const char *cmd, char **directories)
{
	char	*command_path;
	char	*result;
	int		i;

	i = 0;
	result = NULL;
	while (directories[i] != NULL)
	{
		command_path = find_command_in_directory(cmd, directories[i]);
		if (!command_path)
			i++;
		else if (access(command_path, F_OK) == 0)
		{
			result = command_path;
			break ;
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

static void	*search_path(char *env[], int i, char *path)
{
	while (env[++i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = ft_substr(env[i], 5, ft_strlen(env[i]) - 4);
			if (!path)
				return (NULL);
			break ;
		}
	}
	return (path);
}

char	*check_command_existence(const char *cmd, char *env[])
{
	char	*path;
	char	*result;
	char	**directories;
	int		i;

	path = NULL;
	i = -1;
	path = search_path(env, i, path);
	if (path == NULL)
		return (NULL);
	directories = ft_split(path, ':');
	free(path);
	if (!directories)
		return (NULL);
	result = check_command_existence_two(cmd, directories);
	if (!result)
		return (NULL);
	return (result);
}
