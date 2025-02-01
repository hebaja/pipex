/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:00:13 by hebatist          #+#    #+#             */
/*   Updated: 2025/01/31 01:06:38 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

t_cmd	*build_lst_cmd(char **argv, int **fd, char *file_content, char **path)
{
	int			i;
	t_cmd		*lst_cmd;

	i = 1;
	lst_cmd = NULL;
	while (++i < 4)
	{
		if (!compose_cmd(argv[i], &lst_cmd, path))
		{
			clean_path(path);
			clear_all(lst_cmd, fd, file_content);
			exit(EXIT_FAILURE);
		}
	}
	clean_path(path);
	return (lst_cmd);
}

void	init_pipex(char **argv, char **path)
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
	lst_cmd = build_lst_cmd(argv, fd, file_content, path);
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

char	**fetch_path(char **envp)
{
	char		**split_path;
	char		*path;
	int			i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", ft_strlen("PATH")) == 0
			&& envp[i][ft_strlen("PATH")] == '=')
			path = envp[i];
		i++;
	}
	split_path = ft_split(ft_strchr(path, '/'), ':');
	return (split_path);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc == 5)
		init_pipex(argv, fetch_path(envp));
	else
		ft_printf("Wrong number of arguments\n");
	return (0);
}
