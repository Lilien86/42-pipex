/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:05:49 by marvin            #+#    #+#             */
/*   Updated: 2024/02/09 14:40:43 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void free_commands(t_pipex *pipex)
{
	int i;
	int j;

	i = 0;
	while (i < 2) {
		if (pipex->cmds[i] != NULL) {
			j = 0;
			while (pipex->cmds[i][j] != NULL) {
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
		/*if (pipex->infile != NULL)
			free(pipex->infile);
		if (pipex->outfile != NULL)
			free(pipex->outfile);*/
		if (pipex->paths != NULL)
			ft_free_tab(pipex->paths);
		if (pipex->cmds != NULL)
			free_commands(pipex);
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
/*
static char	*find_path_in_env(const char *cmd, char *path)
{
	size_t command_path_len;
	char *command_path;
	while (*path != '\0')
	{
		char *end = ft_strchr(path, ':');
		if (end == NULL)
			end = path + ft_strlen(path);
		command_path_len = (end - path) + ft_strlen(cmd) + 2;
		command_path = (char *)malloc(command_path_len);
		if (!command_path)
			return (NULL);
		ft_strncpy(command_path, path, end - path);
		command_path[end - path] = '/';
		ft_strcpy(command_path + (end - path) + 1, cmd);
		command_path[command_path_len - 1] = '\0';
		if (access(command_path, F_OK) == 0)
			return (command_path);
		if (*end == ':')
			path = end + 1;
		else
		{
			free(command_path);
			break;
		}
		free(command_path);
	}
	return (NULL);
}

char	*check_command_existence(const char *cmd, char *env[])
 {
	char *path;
	int i;

	path = NULL;
	i = 0;
	while (env[i] != NULL) 
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = env[i] + 5;
			break;
		}
		i++;
	}
	if (path == NULL)
		return NULL;
	return (find_path_in_env(cmd, path));
}*/

static char	*find_command_in_directory(const char *cmd, const char *directory)
{
	size_t len_dir = ft_strlen(directory);
	size_t len_cmd = ft_strlen(cmd);
	size_t len_sep = 1;
	size_t command_path_len = len_dir + len_cmd + len_sep;
	char *command_path = (char *)malloc(command_path_len);
	if (!command_path)
		return NULL;
	ft_strcpy(command_path, directory);
	ft_strcat(command_path, "/");
	ft_strcat(command_path, cmd);
	return command_path;
}

char	*check_command_existence(const char *cmd, char *env[])
{
	char *path = NULL;
	int i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = env[i] + 5;
			break;
		}
		i++;
	}
	if (path == NULL)
		return NULL;
	char **directories = ft_split(path, ':');
	if (!directories)
		return NULL;
	char *result = NULL;
	i = 0;
	while (directories[i] != NULL)
	{
		char *command_path = find_command_in_directory(cmd, directories[i]);
		if (!command_path)
		{
			i++;
			continue;
		}
		if (access(command_path, F_OK) == 0)
		{
			result = command_path;
			break;
		}
		free(command_path);
		i++;
	}
	free(directories);
	return result;
}
