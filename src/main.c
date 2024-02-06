/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:29:55 by marvin            #+#    #+#             */
/*   Updated: 2024/02/06 09:29:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex *init_pipex()
{
    t_pipex *pipex;

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

    return (pipex);
}

void    ft_check_args(int ac, char **av, t_pipex *pipex)
{
    pipex->infile = av[1];
    pipex->outfile = av[4];
    if (ac != 5)
    {
        ft_putstr_fd("\033[31mError: Bad arguments\n\e[0m", 2);
        ft_putstr_fd("example of use: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
        exit(EXIT_FAILURE);
    }
    pipex->fd_infile = open(pipex->infile, O_RDONLY);
    if (pipex->fd_infile == -1) {
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


void ft_parse_commands(int ac, char **av, t_pipex *pipex)
{
    (void)ac;
    pipex->cmds = ft_calloc(sizeof(char *), 2);
    pipex->cmds[0] = ft_split(av[2], ' ');
    pipex->cmds[1] = ft_split(av[3], ' ');

}

void print_commands(t_pipex *pipex)
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

int main(int ac, char **av)
{
    t_pipex *pipex;

    pipex = init_pipex();
    ft_check_args(ac, av, pipex);
    ft_parse_commands(ac, av, pipex);

    print_commands(pipex);
    ft_printf("pipex->cmds[0][0] = %s\n", pipex->cmds[0][0]);
    ft_printf("path command -> %s\n", get_command_path(pipex->cmds[0][0]));

    if (access(get_command_path(pipex->cmds[0][0]), X_OK) == 0)
        printf("La commande '%s' est accessible.\n",  pipex->cmds[0][0]);
    else
        printf("La commande '%s' n'est pas accessible.\n",  pipex->cmds[0][0]);

    free_all(pipex);
    return 0;
}