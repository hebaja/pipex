/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:00:13 by hebatist          #+#    #+#             */
/*   Updated: 2025/01/28 16:11:13 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"
#include "../lib/libft/include/libft.h"

#include <signal.h>

t_cmd	*build_lst_cmd(char **argv, t_fds *fds, char *file_content, int cmd_quant)
{
	int			i;
	t_cmd		*lst_cmd;

	i = -1;
	lst_cmd = NULL;
	while (++i < cmd_quant)
	{
		if (!compose_cmd(argv[i], &lst_cmd))
		{
			clear_all(lst_cmd, fds, file_content);
			ft_printf("Could not execute command: %s\n", strerror(EIO));
			exit(EXIT_FAILURE);
		}
	}
	return (lst_cmd);
}

void	init_pipex(char *in_filename, char **argv, int cmd_quant)
{
	char	*file_content;
	t_cmd	*lst_cmd;
	t_fds	*fds;

	fds = init_t_fds(cmd_quant + 1, argv[cmd_quant]);
	if (fds == NULL)
		exit(EXIT_FAILURE);
	file_content = init_infile_content(in_filename);
	if (file_content == NULL)
	{
		clear_fds(fds);
		exit(EXIT_FAILURE);
	}
	if (!init_pipes(fds))
	{
		clear_fds(fds);
		free(file_content);
		exit(EXIT_FAILURE);
	}
	lst_cmd = build_lst_cmd(argv, fds, file_content, cmd_quant);
	if (!exec_pipex(fds, &lst_cmd, file_content, cmd_quant))
		exit(EXIT_FAILURE);
}

void    print_pipe(int cmd_quant)
{
	int i;

	i = 0;
	while (++i < cmd_quant)
		ft_printf("pipe ");
}

void	init_heredoc(char **argv, int cmd_quant)
{
	int		fd;
	char	*str;
	char	*limit;
	
	limit = ft_strjoin(argv[2], "\n");
	fd = open("tempfile", O_WRONLY | O_CREAT | O_TRUNC, 0664);
	print_pipe(cmd_quant);
	ft_printf("here_doc> ");
	str = get_next_line(0);

	if (str == NULL)
	{
		close(fd);
		free(limit);
		exit(EXIT_FAILURE);
	}

	while(strcmp(str, limit) != 0)
	{
		print_pipe(cmd_quant);
		ft_printf("here_doc> ");
		write(fd, str, ft_strlen(str));
		free(str);
		str = get_next_line(0);
		if (str == NULL)
		{
			close(fd);
			free(limit);
			exit(EXIT_FAILURE);
		}
	}

	close(fd);
	free(str);
	free(limit);
	if (access("tempfile", F_OK) < 0 && access("tempfile", R_OK) < 0)
		perror("Could not access file");
	else
		init_pipex("tempfile", &argv[3], cmd_quant);
}

int	main(int argc, char **argv)
{
	if (argc >= 5)
	{
		if (strcmp(argv[1], "here_doc") == 0)
		{
			if (argc >= 6)
				init_heredoc(argv, argc - 4);
			else
			{
				ft_printf("Insufficient number of arguments\n");
				return (0);
			}
		}
		else
			init_pipex(argv[1], &argv[2], argc - 3);
	}
	else
		ft_printf("Insufficient number of arguments\n");
	return (0);
}
