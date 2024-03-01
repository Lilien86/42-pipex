/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:29:45 by lauger            #+#    #+#             */
/*   Updated: 2024/03/01 20:33:20 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipe(int pipefd[2], t_pipex *pipex)
{
	if (pipefd && pipefd[0] != -1)
		close(pipefd[0]);
	if (pipefd && pipefd[1] != -1)
		close(pipefd[1]);
	if (pipex->pipe_hd[0] != -1)
		close(pipex->pipe_hd[0]);
	if (pipex->pipe_hd[1] != -1)
		close(pipex->pipe_hd[1]);
	if (pipex->fd_outfile != -1)
		close(pipex->fd_outfile);
	if (pipex->fd_infile != -1)
		close(pipex->fd_infile);
}

static void	handle_child_two(int pipefd[2], t_pipex *pipex, int i)
{
	if (i == pipex->nb_exec - 1)
	{
		dup2(pipex->fd_outfile, STDOUT_FILENO);
		if (pipex->fd_infile != -1)
			close(pipex->fd_infile);
	}
	else
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	close_pipe(pipefd, pipex);
	if (!pipex->paths[i])
	{
		free_all(pipex);
		ft_putstr_fd("\033[31mError:\ncommand not found:\033[0m", 2);
		exit(EXIT_FAILURE);
	}
	execve(pipex->paths[i], pipex->cmds[i], pipex->env);
}

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
		if (pipex->fd_infile != -1)
			close(pipex->fd_infile);
	}
	handle_child_two(pipefd, pipex, i);
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
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
}

void	handle_execution(t_pipex *pipex, int i, char **av)
{

	pipex->nb_exec = pipex->nb_elems;
	if (ft_strncmp(av[1], "here_doc", ft_strlen("here_doc")) == 0)
	{
		//if (pipex->fd_outfile == -1 || pipex->cmds[pipex->nb_elems] == NULL)
		pipex->nb_exec--;
		while (i < pipex->nb_exec)
		{
			ft_exec_here_doc(pipex, i);
			i++;
		}
	}
	else
	{
		//if (pipex->fd_outfile == -1 || pipex->cmds[pipex->nb_elems] == NULL)
		pipex->nb_exec--;
		while (i < pipex->nb_exec)
		{
			ft_exec(pipex, i);
			i++;
		}
	}
	handle_wait(pipex);
}
