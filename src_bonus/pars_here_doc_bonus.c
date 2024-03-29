/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_here_doc_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 09:05:20 by lauger            #+#    #+#             */
/*   Updated: 2024/03/08 11:12:12 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	is_limiter(char *line, char *tmp, char *limiter)
{
	if (!line || !limiter || !tmp)
	{
		return (0);
	}
	if (ft_strncmp(tmp, limiter, ft_strlen(limiter)) == 0
		&& ft_strlen(tmp) == ft_strlen(limiter) + 1)
		return (1);
	return (0);
}

static void	handle_while_two(char **line, char **tmp)
{
	if ((*line && (*line)[0] == '\0')
		|| (*line && (*line)[ft_strlen(*line) - 1] == '\n'))
	{
		write (1, "here_doc > ", 11);
		free(*tmp);
		*tmp = NULL;
	}
	else
		free(*tmp);
}

static void	handle_while(char **line, char **tmp, char *limiter)
{
	static char	*buffer;

	while (true)
	{
		handle_while_two(line, tmp);
		*tmp = get_next_line(0, &buffer);
		if (*tmp)
		{
			if (is_limiter(*line, *tmp, limiter) == 0)
				*line = ft_strjoin(*line, *tmp);
			else if (*line && is_limiter(*line, *tmp, limiter) == 1)
			{
				free(buffer);
				buffer = NULL;
				break ;
			}
		}
		else if ((*line)[0] == '\0' || (*line)[ft_strlen(*line) - 1] == '\n')
		{
			free(buffer);
			buffer = NULL;
			ft_printf("\nError:\na limiter is expected\n");
			break ;
		}
	}
}

static void	handle_child(char *limiter, t_pipex *pipex)
{
	char	*line;
	char	*tmp;

	tmp = ft_calloc(1, 1);
	line = ft_calloc(1, 1);
	if (!tmp || !line)
		return ;
	close(pipex->pipe_hd[0]);
	handle_while(&line, &tmp, limiter);
	write(pipex->pipe_hd[1], line, ft_strlen(line));
	free(line);
	free(tmp);
	close_pipe(NULL, pipex, -1);
	free_all(pipex);
	exit(0);
}

void	handle_here_doc(char *limiter, t_pipex *pipex)
{
	pid_t	pid;

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
		handle_child(limiter, pipex);
	waitpid(-1, NULL, 0);
	close(pipex->pipe_hd[1]);
}
