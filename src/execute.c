/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:29:45 by lauger            #+#    #+#             */
/*   Updated: 2024/03/08 14:04:29 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	handle_child_two(int pipefd[2], t_pipex *pipex, int i)
{
	if (i == pipex->nb_elems - 1)
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
	close_pipe(pipefd, pipex, -1);
	if (!pipex->paths[i])
	{
		ft_putstr_fd("\033[31mError:\ncommand not found:\n\033[0m", 2);
		close_pipe(NULL, pipex, 1);
		close_pipe(pipefd, pipex, -1);
		free_all(pipex);
		exit(EXIT_FAILURE);
	}
	execve(pipex->paths[i], pipex->cmds[i], pipex->env);
}

static void	handle_child(int pipefd[2], t_pipex *pipex, int i)
{
	if (close(pipefd[0]) == -1)
	{
		perror("Error:\nclose\n");
		close_pipe(pipefd, pipex, -1);
		close_pipe(NULL, pipex, 1);
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
		close_pipe(pipefd, pipex, -1);
		close_pipe(NULL, pipex, 1);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		handle_child(pipefd, pipex, i);
	}
	close(pipefd[1]);
	if (i == pipex->nb_elems - 1)
	{
		dup2(pipefd[0], pipex->fd_outfile);
	}
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close_pipe(pipefd, pipex, 0);
}

void	handle_execution(t_pipex *pipex, int i, char **av)
{
	int	size;

	size = pipex->nb_elems;
	if (ft_strncmp(av[1], "here_doc", ft_strlen("here_doc")) == 0)
	{
		if (pipex->fd_outfile == -1)
			size--;
		while (i < size)
			ft_exec_here_doc(pipex, i++);
	}
	else
	{
		if (pipex->existance_infile == 1)
			i++;
		if (pipex->fd_outfile == -1)
			size--;
		while (i < size)
		{
			ft_exec(pipex, i);
			i++;
		}
	}
	handle_wait(pipex);
}
