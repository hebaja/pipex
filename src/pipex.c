/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:00:13 by hebatist          #+#    #+#             */
/*   Updated: 2025/01/27 20:44:52 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

t_cmd	*build_lst_cmd(char **argv, int **fd, char *file_content)
{
	int			i;
	t_cmd		*lst_cmd;

	i = 1;
	lst_cmd = NULL;
	while (++i < 4)
	{
		if (!compose_cmd(argv[i], &lst_cmd))
		{
			clear_all(lst_cmd, fd, file_content);
			exit(EXIT_FAILURE);
		}
	}
	return (lst_cmd);
}

void	init_pipex(char **argv)
{
	int		**fd;
	int		out_fd;
	char	*file_content;
	t_cmd	*lst_cmd;

	fd = init_fd(3);
	if (!init_pipes(fd, 3)
		|| !init_files(argv[1], argv[4], &file_content, &out_fd))
	{
		clear_fd(fd, 3);
		exit(EXIT_FAILURE);
	}
	lst_cmd = build_lst_cmd(argv, fd, file_content);
	if (lst_cmd)
	{
		if (!exec_pipex(fd, &lst_cmd, file_content, out_fd))
			exit(EXIT_FAILURE);
	}
	else
	{
		clear_all(lst_cmd, fd, file_content);
		ft_printf("Could not execute command: %s\n", strerror(EIO));
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv)
{
	if (argc == 5)
		init_pipex(argv);
	else
		ft_printf("Wrong number of arguments\n");
	return (0);
}
