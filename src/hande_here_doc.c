/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hande_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 09:05:20 by lauger            #+#    #+#             */
/*   Updated: 2024/02/16 13:52:17 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	handle_child(char *limiter, t_pipex *pipex, int fd_stdin)
{
	char	*line;

	close(pipex->pipe_hd[0]);
	while (true)
	{
		line = get_next_line(0);
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			get_next_line(-12);
			break ;
		}
		write(pipex->pipe_hd[1], line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(pipex->pipe_hd[1]);
	exit(0);
}

void	handle_here_doc(char *limiter, t_pipex *pipex)
{
	pid_t	pid;
	int		fd_stdin;

	// fd_stdin = dup(0);
	if (pipe(pipex->pipe_hd) == -1)
	{
		perror("\033[31mError:\nto use the pipe\n\e[0m");
		free_all(pipex);
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("\033[31mError:\nto use the fork\n\e[0m");
		free_all(pipex);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		handle_child(limiter, pipex, fd_stdin);
	}
	waitpid(-1, NULL, 0);
	close(pipex->pipe_hd[1]);
}
