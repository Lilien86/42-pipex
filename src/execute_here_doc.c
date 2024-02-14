/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_here_doc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:05:39 by lauger            #+#    #+#             */
/*   Updated: 2024/02/14 13:59:47 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exec_here_doc(t_pipex *pipex, int i)
{
	int	pipefd[2];
	pid_t pid;

	if(pipe(pipefd) < 0)
	{
		free(pipex);
		perror("\033[31mError:\nto use the pipe\n\e[0m");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		free(pipex);
		perror("\033[31mError:\nto use the fork\n\e[0m");
		exit(EXIT_FAILURE);
	}
	else if(pid == 0)
	{
		if (close(pipefd[0]) == -1)
		{
			free(pipex);
			perror("\033[31mError:\nto use the pipe\n\e[0m");
			exit(EXIT_FAILURE);
		}
		if (i == 0)
		{
			if(dup2(pipex->pipe_hd[0], STDIN_FILENO) == -1)
			{
				free(pipex);
				perror("\033[31mError:\nto use the function dup2\n\e[0m");
				exit(EXIT_FAILURE);
			}
			close(pipex->pipe_hd[0]);
		}
		if (i == pipex->nb_elems)
		{
			if(dup2(pipex->pipe_hd[1], STDOUT_FILENO) == -1)
			{
				free(pipex);
				perror("\033[31mError:\nto use the function dup2\n\e[0m");
				exit(EXIT_FAILURE);
			}
			close(pipex->pipe_hd[1]);
		}
		else
		{
			if(dup2(pipefd[1], STDOUT_FILENO) == -1)
			{
				free(pipex);
				perror("\033[31mError:\nto use the function dup2\n\e[0m");
				exit(EXIT_FAILURE);
			}
			close(pipefd[1]);
		}
		execve(pipex->paths[i], pipex->cmds[i], NULL);
		perror("\033[31mErreur:\nduring execution of the command\n\e[0m");
	}
	else
	{
		close(pipefd[1]);
		waitpid(-1, NULL, 0);
		dup2(pipefd[0], STDIN_FILENO);
	}
}

