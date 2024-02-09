/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:29:55 by marvin            #+#    #+#             */
/*   Updated: 2024/02/09 14:36:39 by lauger           ###   ########.fr       */
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

	pipex = malloc(sizeof(t_pipex));
	if (pipex == NULL)
	{
		perror("Error:\nfailure to allocate pipex");
		exit(EXIT_FAILURE);
	}
	pipex->fd_infile = 0;
	pipex->fd_outfile = 0;
	pipex->infile = NULL;
	pipex->outfile = NULL;
	pipex->cmds = NULL;
	pipex->cmds = NULL;

	return (pipex);
}

void	ft_check_args(int ac, char **av, t_pipex *pipex)
{
	pipex->infile = av[1];
	pipex->outfile = av[ac - 1];
	if (ac != 5)
	{
		ft_putstr_fd("\033[31mError: Bad arguments\n\e[0m", 2);
		ft_putstr_fd("example of use: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
		exit(EXIT_FAILURE);
	}
	pipex->fd_infile = open(pipex->infile, O_RDONLY);
	if (pipex->fd_infile == -1)
	{
		perror("\033[31mErreur: to open the input file\n\e[0m");
		exit(EXIT_FAILURE);
	}
	pipex->fd_outfile = open(pipex->outfile, O_WRONLY, 0644);
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

	i = 2;
	j = 0;
	pipex->cmds = ft_calloc(sizeof(char *), ac - 3);
	pipex->paths = ft_calloc(sizeof(char *), ac - 3);
	if (!pipex->cmds || !pipex->paths)
		return ;
	while (i < (ac - 1))
	{
		pipex->cmds[j] = ft_split(av[i], ' ');
		if (is_path(pipex->cmds[j][0]) == 1)
		{
			pipex->paths[j] = ft_strdup(pipex->cmds[j][0]);
			if (access(pipex->paths[j], X_OK) == 0)
				printf("La commande '%s' is accessible.\n",  pipex->cmds[j][0]);
			else
				printf("La commande '%s' is not accessible.\n",  pipex->cmds[j][0]);
		}
		else
		{
			pipex->paths[j] = ft_strdup(check_command_existence(pipex->cmds[j][0], env));
			if (pipex->paths[j] == NULL)
				printf("command '%s' is not accessible.\n",  pipex->cmds[j][0]);
			else
				printf("command '%s' is accessible.\n",  pipex->cmds[j][0]);
		}
		i++;
		j++;
	}
}

int	main(int ac, char **av, char *env[])
{
	t_pipex	*pipex;

	pipex = init_pipex();
	ft_check_args(ac, av, pipex);
	ft_parse_commands(ac, av, pipex, env);

	free_all(pipex);
	return (0);
}