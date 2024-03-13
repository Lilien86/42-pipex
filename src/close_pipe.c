/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:58:45 by lauger            #+#    #+#             */
/*   Updated: 2024/03/08 14:02:49 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_sdt(void)
{
	if (STDOUT_FILENO != -1)
		close(STDOUT_FILENO);
	if (STDIN_FILENO != -1)
		close(STDIN_FILENO);
	if (STDERR_FILENO != -1)
		close(STDERR_FILENO);
}

void	close_pipe(int pipefd[2], t_pipex *pipex, int status)
{
	if (status <= 0)
	{
		if (pipefd && pipefd[0] != -1)
			close(pipefd[0]);
		if (pipefd && pipefd[1] != -1)
			close(pipefd[1]);
		if (pipex->pipe_hd[0] != -1)
			close(pipex->pipe_hd[0]);
		if (pipex->pipe_hd[1] != -1)
			close(pipex->pipe_hd[1]);
		if (status == -1)
		{
			if (pipex->fd_infile != -1)
				close(pipex->fd_infile);
			if (pipex->fd_outfile != -1)
				close(pipex->fd_outfile);
		}
	}
	else
	{
		close_sdt();
	}
}
