/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:29:55 by marvin            #+#    #+#             */
/*   Updated: 2024/02/14 12:15:35 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_commands(t_pipex *pipex)
{
	int i, j;
	for (i = 0; i < 2; i++)
	{
		printf("\033[31mCommande %d : \n\e[0m", i + 1);
		if (pipex->cmds[i] == NULL) {
			printf("NULL\n");
			continue;
		}
		for (j = 0; pipex->cmds[i][j] != NULL; j++)
		{
			printf("%s \n", pipex->cmds[i][j]);
		}
		printf("-----\n");
	}
}

t_pipex	*init_pipex()
{
	t_pipex	*pipex;

	pipex = ft_calloc(sizeof(t_pipex), 1);
	if (pipex == NULL)
	{
		perror("Error:\nfailure to allocate pipex");
		exit(EXIT_FAILURE);
	}
	pipex->nb_elems = 0;
	pipex->fd_infile = 0;
	pipex->fd_outfile = 0;
	pipex->infile = NULL;
	pipex->outfile = NULL;
	pipex->pipe_hd[0] = -1;
	pipex->pipe_hd[1] = -1;
	pipex->cmds = NULL;
	pipex->cmds = NULL;

	return (pipex);
}

void	ft_check_args(int ac, char **av, t_pipex *pipex)
{
	if (ft_strncmp(av[1], "here_doc", ft_strlen("here_doc")) == 0)
	{
		handle_here_doc(av[2], pipex);
	}
	else
	{
		pipex->infile = av[1];
		pipex->fd_infile = open(pipex->infile, O_RDONLY);
		if (pipex->fd_infile == -1)
		{
			perror("\033[31mErreur: to open the input file\n\e[0m");
			exit(EXIT_FAILURE);
		}
	}
	pipex->outfile = av[ac - 1];
	pipex->fd_outfile = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->fd_outfile == -1)
	{
		perror("\033[31mErreur: to open the output file\n\e[0m");
		exit(EXIT_FAILURE);
	}
}


void	ft_parse_commands(int ac, char **av, t_pipex *pipex, char *env[])
{
	(void)env;
	int	i;
	int	j;
	int	k;

	i = 2;
	j = 0;
	k = 0;
	pipex->cmds = ft_calloc(sizeof(char *), ac - 2);
	pipex->paths = ft_calloc(sizeof(char *), ac - 2);
	if (!pipex->cmds || !pipex->paths)
		return ;
	if (ft_strncmp(av[1], "here_doc", ft_strlen("here_doc")) == 0)
	{
		k += 1;
		i += k;
	}
	while (i < (ac - 1))
	{
		pipex->cmds[j] = ft_split(av[i], ' ');
		if (is_path(pipex->cmds[j][0]) == 1)
		{
			pipex->paths[j] = ft_strdup(pipex->cmds[j][0]);
			if (access(pipex->paths[j], X_OK) == 0)
				printf("'%s' is accessible.\n",  pipex->cmds[j][0]);
			else
				printf("'%s' is not accessible.\n",  pipex->cmds[j][0]);
		}
		else
		{
			pipex->paths[j] = check_command_existence(pipex->cmds[j][0], env);
			if (pipex->paths[j] == NULL)
				printf("'%s' is not accessible.\n",  pipex->cmds[j][0]);
			else
				printf("'%s' is accessible.\n",  pipex->cmds[j][0]);
		}
		i++;
		j++;
	}
	pipex->nb_elems = i - (3 + k);
}

int	main(int ac, char **av, char *env[])
{
	t_pipex	*pipex;
	int		i;

	i = 0;
	pipex = init_pipex();
	ft_check_args(ac, av, pipex);
	ft_parse_commands(ac, av, pipex, env);
	if (ft_strncmp(av[1], "here_doc", ft_strlen("here_doc")) == 0)
	{
		while (pipex->cmds[i])
		{
			ft_exec_here_doc(pipex, i);
			i++;
		}
	}
	else
	{
		while (pipex->cmds[i])
		{
			ft_exec(pipex, i);
			i++;
		}
	}
	close(pipex->fd_infile);
	close(pipex->fd_outfile);
	free_all(pipex);
	return (0);
}
