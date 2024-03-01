/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:05:49 by marvin            #+#    #+#             */
/*   Updated: 2024/03/01 09:54:59 by lauger           ###   ########.fr       */
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

static char	*check_command_existence_two(const char *cmd, char *env[],
	char **directories, char	*result)
{
	char	*command_path;
	int		i;

	i = 0;
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

char	*check_command_existence(const char *cmd, char *env[])
{
	char	*path;
	char	*result;
	char	**directories;
	int		i;

	path = NULL;
	i = -1;
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
	if (path == NULL)
		return (NULL);
	directories = ft_split(path, ':');
	free(path);
	if (!directories)
		return (NULL);
	result = NULL;
	return (check_command_existence_two(cmd, env, directories, result));
}
