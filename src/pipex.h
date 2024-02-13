/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:07:07 by lauger            #+#    #+#             */
/*   Updated: 2024/02/13 10:47:14 by lauger           ###   ########.fr       */
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

typedef struct	s_pipex
{
	int			nb_elems;
	int			fd_infile;
    int			fd_outfile;
	char		*infile;
	char		*outfile;
	char		***cmds;
	char		**paths;

}	t_pipex;

void	free_all(t_pipex *pipex);
char	*get_command_path(const char *command_name);
char	*check_command_existence(const char *cmd, char *env[]);
int		is_path(char *s);
void	ft_exec(t_pipex *pipex, int i);

#endif
