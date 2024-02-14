/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hande_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 09:05:20 by lauger            #+#    #+#             */
/*   Updated: 2024/02/14 13:54:37 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void handle_here_doc(char *limiter, t_pipex *pipex)
{
	pid_t	pid;
	char	*line;
	int fd_stdin = dup(0);
	
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
		close(pipex->pipe_hd[0]);
		while(true)
		{
			line = get_next_line(fd_stdin);
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				break;
			write(pipex->pipe_hd[1], line, ft_strlen(line));
			free(line);
		}
		close(pipex->pipe_hd[1]);
	}
	else
	{
		waitpid(-1, NULL, 0);
		close(pipex->pipe_hd[1]);
	}
}
