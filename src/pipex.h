/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:07:07 by lauger            #+#    #+#             */
/*   Updated: 2024/02/08 14:32:31 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft.h"

# define MAX_PATH_LENGTH 256

typedef struct	s_pipex
{
	int			fd_infile;
    int			fd_outfile;
	char		*infile;
	char		*outfile;
	char		***cmds;

}	t_pipex;

void free_all(t_pipex *pipex);
char *get_command_path(const char *command_name);
char *check_command_existence(const char *cmd, char *env[]);
int	is_path(char *s);

#endif
