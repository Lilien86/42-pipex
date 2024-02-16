/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_here_doc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:05:39 by lauger            #+#    #+#             */
/*   Updated: 2024/02/16 14:00:44 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*void	close_fd(t_pipex *pipex, int pipefd[2])
{
	if (close(pipefd[0]) == -1 | close(pipefd[1]) == -1
		| close(pipex->pipe_hd[0]) == -1 | close(pipex->pipe_hd[1]) == -1
		| close(pipex->fd_outfile) == -1)
	{
		free_all(pipex);
		perror("Error:\nclosing file descriptor");
		exit(EXIT_FAILURE);
	}
}*/

static void	handle_child(int pipefd[2], t_pipex *pipex, int i)
{
	if (close(pipefd[0]) == -1)
	{
		perror("\033[31mError:\nto use the pipe\n\e[0m");
		exit(EXIT_FAILURE);
	}
	if (i == 0)
	{
		dup2(pipex->pipe_hd[0], STDIN_FILENO);
		//close(pipex->pipe_hd[0]);
	}
	if (i == pipex->nb_elems - 1)
	{
		dup2(pipex->pipe_hd[1], STDOUT_FILENO);
		//close(pipex->pipe_hd[1]);
	}
	else
	{
		dup2(pipefd[1], STDOUT_FILENO);
		//close(pipefd[1]);
	}
	//close_fd(pipex, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);

	close(pipex->pipe_hd[0]);
	close(pipex->fd_outfile);
	if (pipex->paths[i] != NULL)
		execve(pipex->paths[i], pipex->cmds[i], NULL);
	perror("\033[31mError:\nduring execution of the command\n\e[0m");
	exit(EXIT_SUCCESS);
}

void	ft_exec_here_doc(t_pipex *pipex, int i)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) < 0)
	{
		free_all(pipex);
		perror("\033[31mError:\nto use the pipe\n\e[0m");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		free_all(pipex);
		perror("\033[31mError:\nto use the fork\n\e[0m");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		handle_child(pipefd, pipex, i);
	}
	else
	{
		close(pipefd[1]);
		waitpid(pid, NULL, 0);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipex->pipe_hd[0]);
		close(pipefd[0]);
	}
}
