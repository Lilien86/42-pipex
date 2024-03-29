/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:07:07 by lauger            #+#    #+#             */
/*   Updated: 2024/03/08 13:59:16 by lauger           ###   ########.fr       */
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
# include <stdbool.h>

typedef struct s_pipex
{
	int			nb_elems;
	int			fd_infile;
	int			fd_outfile;
	int			pipe_hd[2];
	int			here_doc;
	int			existance_infile;
	char		*infile;
	char		*outfile;
	char		***cmds;
	char		**paths;
	char		**env;

}	t_pipex;

void	free_all(t_pipex *pipex);
char	*check_command_existence(const char *cmd, char *env[]);
int		is_path(char *s);
void	ft_exec(t_pipex *pipex, int i);
void	ft_exec_here_doc(t_pipex *pipex, int i);
void	handle_here_doc(char *limiter, t_pipex *pipex);
void	ft_check_args(int ac, char **av, t_pipex *pipex);
void	ft_parse_commands_two(int ac, char **av, t_pipex *pipex, int i);
void	ft_parse_commands(int ac, char **av, t_pipex *pipex, char *env[]);
void	handle_execution(t_pipex *pipex, int i, char **av);
void	handle_wait(t_pipex *pipex);
void	close_pipe(int pipefd[2], t_pipex *pipex, int status);

#endif
