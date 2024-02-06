/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:05:49 by marvin            #+#    #+#             */
/*   Updated: 2024/02/06 11:05:49 by marvin           ###   ########.fr       */
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

char *ft_strcat(char *dest, const char *src) {
    char *ptr = dest;
    while (*dest)
        dest++;
    while ((*dest++ = *src++))
        ;
    *dest = '\0';
    return ptr;
}


char *get_command_path(const char *command_name)
{
    char *command_path = NULL;
    char *standard_paths[] = {"/bin", "/usr/bin", "/usr/local/bin", NULL};

    int i = 0;
    while (standard_paths[i] != NULL)
    {
        char *full_path = malloc(MAX_PATH_LENGTH);
        if (full_path == NULL)
        {
            perror("Error: \nto alocate memory");
            exit(EXIT_FAILURE);
        }
        ft_strcpy(full_path, standard_paths[i]);
        ft_strcat(full_path, "/");
        ft_strcat(full_path, command_name);
        if (access(full_path, X_OK) == 0)
        {
            command_path = strdup(full_path);
            break;
        }
        free(full_path);
        i++;
    }

    return (command_path);
}

