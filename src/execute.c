/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:29:45 by lauger            #+#    #+#             */
/*   Updated: 2024/02/16 12:41:05 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	handle_child(int pipefd[2], t_pipex *pipex, int i)
{
	if (close(pipefd[0]) == -1)
	{
		perror("Error:\nclose\n");
		exit(EXIT_FAILURE);
	}
	if (i == 0)
	{
		dup2(pipex->fd_infile, STDIN_FILENO);
		close(pipex->fd_infile);
	}
	if (i == pipex->nb_elems - 1)
	{
		dup2(pipex->fd_outfile, STDOUT_FILENO);
		close(pipex->fd_infile);
	}
	else
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	if (pipex->paths[i] != NULL)
		execve(pipex->paths[i], pipex->cmds[i], NULL);
	perror("\033[31mError:\nduring execution of the child process\n\e[0m");
	exit(EXIT_SUCCESS);
}

void	ft_exec(t_pipex *pipex, int i)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) < 0)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
	{
		perror("Error:\nfork\n");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		handle_child(pipefd, pipex, i);
	}
	close(pipefd[1]);
	waitpid(-1, NULL, 0);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
}
