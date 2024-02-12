/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:29:45 by lauger            #+#    #+#             */
/*   Updated: 2024/02/12 15:18:26 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_exec(t_pipex *pipex, int i)
{
	int	pipe[2];

	if(pipe(pipe) < 0)
		exit(EXIT_FAILURE);
	pid_t pid;
	if ((pid = fork()) == -1)
	{
		perror("Error:\nfork\n");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{ // Processus enfant
		if (i == 0)
		{
			dup2(pipex->fd_infile, STDIN_FILENO);
			close(pipex->fd_infile);
		}
		if (i == nb_arg - 1)
		{
			dup2(pipex->fd_infile, STDIN_FILENO);
		}
		{
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
		}

		
	}
}