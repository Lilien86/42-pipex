/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:29:55 by marvin            #+#    #+#             */
/*   Updated: 2024/03/05 12:25:47 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_pipex	*init_pipex(void)
{
	t_pipex	*pipex;

	pipex = ft_calloc(sizeof(t_pipex), 1);
	if (pipex == NULL)
	{
		perror("Error:\nfailure to allocate pipex\n");
		exit(EXIT_FAILURE);
	}
	pipex->nb_elems = 0;
	pipex->fd_infile = 0;
	pipex->fd_outfile = 0;
	pipex->here_doc = 0;
	pipex->existance_infile = -1;
	pipex->pipe_hd[0] = -1;
	pipex->pipe_hd[1] = -1;
	pipex->infile = NULL;
	pipex->outfile = NULL;
	pipex->cmds = NULL;
	pipex->cmds = NULL;
	return (pipex);
}

int	main(int ac, char **av, char *env[])
{
	t_pipex	*pipex;
	int		i;

	i = 0;
	if (ac >= 5 && ac <= 512)
	{
		pipex = init_pipex();
		ft_check_args(ac, av, pipex);
		ft_parse_commands(ac, av, pipex, env);
		handle_execution(pipex, i, av);
		if (pipex->fd_infile != -1)
			close(pipex->fd_infile);
		if (pipex->fd_outfile != -1)
			close(pipex->fd_outfile);
		free_all(pipex);
	}
	else
		ft_putstr_fd("\033[31mError:\nbad arguments \033[0m: is expected :\n"
			"./pipex infile cmd1 cmd2 outfile", 2);
	return (0);
}
