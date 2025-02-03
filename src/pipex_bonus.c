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

void	init_pipex(char *in_filename, char **argv, char **path)
{
	char	*file_content;
	t_cmd	*lst_cmd;
	t_fds	*fds;
	size_t	cmd_quant;

	cmd_quant = get_cmd_quant(argv);
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
	lst_cmd = build_lst_cmd(argv, fds, file_content, path);
	if (!exec_pipex(fds, &lst_cmd, file_content, cmd_quant))
		exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc >= 5)
	{
		if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
		{
			if (argc >= 6)
				init_here_doc(argv, fetch_path(envp));
			else
			{
				ft_printf("Insufficient number of arguments\n");
				return (0);
			}
		}
		else
			init_pipex(argv[1], &argv[2], fetch_path(envp));
	}
	else
		ft_printf("Insufficient number of arguments\n");
	return (0);
}
