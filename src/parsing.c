/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:32:22 by lauger            #+#    #+#             */
/*   Updated: 2024/03/05 09:31:10 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_check_args_two(int ac, char **av, t_pipex *pipex)
{
	if (av[ac - 1][0] == '\0')
	{
		perror("\033[31mError:\nto open the output file \e[0m");
	}
	pipex->outfile = av[ac - 1];
	if (ft_strncmp(av[1], "here_doc", ft_strlen("here_doc")) == 0)
		pipex->fd_outfile = open(pipex->outfile, O_WRONLY
				| O_CREAT | O_APPEND, 0644);
	else
		pipex->fd_outfile = open(pipex->outfile, O_WRONLY
				| O_CREAT | O_TRUNC, 0644);
	if (pipex->fd_outfile == -1)
		ft_putstr_fd("\033[31mError:\nto open the output file \e[0m", 2);
}

void	ft_check_args(int ac, char **av, t_pipex *pipex)
{
	if (ft_strncmp(av[1], "here_doc", ft_strlen("here_doc")) == 0)
		handle_here_doc(av[2], pipex);
	else
	{
		pipex->infile = av[1];
		pipex->fd_infile = open(pipex->infile, O_RDONLY);
		if (pipex->fd_infile == -1)
		{
			perror("\033[31mError:\nto open the input file \e[0m");
			pipex->existance_infile = 1;
		}
	}
	ft_check_args_two(ac, av, pipex);
}

void	ft_parse_commands_two(int ac, char **av, t_pipex *pipex, int i)
{
	int	j;

	j = 0;
	while (i < (ac - 1))
	{
		pipex->cmds[j] = ft_split(av[i], ' ');
		if (!pipex->cmds[j] || pipex->cmds[j][0] == NULL)
		{
			i++;
			j++;
			continue ;
		}
		if (is_path(pipex->cmds[j][0]) == 1)
			pipex->paths[j] = ft_strdup(pipex->cmds[j][0]);
		else
			pipex->paths[j] = check_command_existence
				(pipex->cmds[j][0], pipex->env);
		i++;
		j++;
	}
}

void	ft_parse_commands(int ac, char **av, t_pipex *pipex, char *env[])
{
	int	i;

	i = 2;
	if (*av[ac - 2] == '\0')
		ac --;
	pipex->env = env;
	pipex->cmds = ft_calloc(sizeof(char *), ac - 2);
	pipex->paths = ft_calloc(sizeof(char *), ac - 2);
	if (!pipex->cmds || !pipex->paths)
		return ;
	if (ft_strncmp(av[1], "here_doc", ft_strlen("here_doc")) == 0)
	{
		i++;
		pipex->here_doc += 1;
	}
	ft_parse_commands_two(ac, av, pipex, i);
	pipex->nb_elems = ac - 3 - pipex->here_doc;
}

void	handle_wait(t_pipex *pipex)
{
	int	status;
	int	i;

	i = 0;
	while (i < pipex->nb_elems)
	{
		wait(&status);
		i++;
	}
}
