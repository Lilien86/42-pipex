/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:29:45 by lauger            #+#    #+#             */
/*   Updated: 2024/02/15 14:30:41 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exec(t_pipex *pipex, int i)
{
	int	pipefd[2];
	pid_t pid;

	if(pipe(pipefd) < 0)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
	{
		perror("Error:\nfork\n");
		exit(EXIT_FAILURE);
	}
	else if(pid == 0)
	{
		if (close(pipefd[0]) == -1)
		{
			perror("Error:\nclose\n");
			exit(EXIT_FAILURE);
		}
		if (i == 0)
		{
			if(dup2(pipex->fd_infile, STDIN_FILENO) == -1)
			{
				perror("Error:\ndup2\n");
				exit(EXIT_FAILURE);
			}
			close(pipex->fd_infile);
		}
		if (i == pipex->nb_elems - 1)
		{
			if(dup2(pipex->fd_outfile, STDOUT_FILENO) == -1)
			{
				perror("Error:\ndup2\n");
				exit(EXIT_FAILURE);
			}
			close(pipex->fd_infile);
		}
		else
		{
			if(dup2(pipefd[1], STDOUT_FILENO) == -1)
			{
				perror("Error:\ndup2\n");
				exit(EXIT_FAILURE);
			}
			close(pipefd[1]);
		}
		if (pipex->paths[i] != NULL)
			execve(pipex->paths[i], pipex->cmds[i], NULL);
		perror("\033[31mError:\nduring execution of the child process\n\e[0m");
	}
	else
	{
		close(pipefd[1]);
		waitpid(-1, NULL, 0);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
}
