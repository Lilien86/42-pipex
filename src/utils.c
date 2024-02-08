/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:05:49 by marvin            #+#    #+#             */
/*   Updated: 2024/02/08 14:32:18 by lauger           ###   ########.fr       */
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
		if (pipex->cmds != NULL)
			free_commands(pipex);
	}
	free(pipex);
}

char *ft_strcpy(char *dest, const char *src)
{
	char *ptr = dest;
	while ((*dest++ = *src++))
		;
	return ptr;
}

char *ft_strcat(char *dest, const char *src)
{
	char *ptr = dest;
	while (*dest)
		dest++;
	while ((*dest++ = *src++))
		;
	*dest = '\0';
	return ptr;
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

char *ft_strncpy(char *dest, const char *src, size_t n) {
	size_t i = 0;
	while (i < n && src[i] != '\0') {
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return dest;
}
/*int check_command_existence(const char *cmd, char *env[])
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
	{
		ft_printf("Error: PATH variable not found in environment\n");
		return (0);
	}
	while (*path != '\0')
	{
		char command_path[1024];
		char *end = strchr(path, ':');
		if (end == NULL)
			end = path + strlen(path);
		ft_strncpy(command_path, path, end - path);
		command_path[end - path] = '\0';
		ft_strcat(command_path, "/");
		ft_strcat(command_path, cmd);

		if (access(command_path, F_OK) == 0)
			return 1;

		if (*end == ':')
			path = end + 1;
		else
			break;
	}

	return 0;
}*/

char *check_command_existence(const char *cmd, char *env[])
 {
	char *path = NULL;
	int i = 0;

	while (env[i] != NULL) {
		if (strncmp(env[i], "PATH=", 5) == 0)
		{
			path = env[i] + 5;
			break;
		}
		i++;
	}
	if (path == NULL)
	{
		fprintf(stderr, "Error: PATH variable not found in environment\n");
		return NULL;
	}

	while (*path != '\0')
	{
		char *end = strchr(path, ':');
		if (end == NULL)
			end = path + strlen(path);

		size_t command_path_len = (end - path) + strlen(cmd) + 2;
		char *command_path = (char *)malloc(command_path_len);
		if (command_path == NULL) {
			perror("Error");
			return NULL;
		}
		strncpy(command_path, path, end - path);
		command_path[end - path] = '/';
		strcpy(command_path + (end - path) + 1, cmd);
		command_path[command_path_len - 1] = '\0';

		if (access(command_path, F_OK) == 0)
			return command_path;

		if (*end == ':')
			path = end + 1;
		else
			break;

		free(command_path);
	}

	return NULL;
}