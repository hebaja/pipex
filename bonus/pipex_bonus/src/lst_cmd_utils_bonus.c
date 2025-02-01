/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:58:30 by hebatist          #+#    #+#             */
/*   Updated: 2025/01/23 22:48:48 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

size_t	get_cmd_quant(char **argv)
{
	size_t	quant;

	quant = 0;
	while (argv[quant])
		quant++;
	return (quant -1);
}

void	lst_cmd_clear(t_cmd **lst_cmd)
{
	int		i;
	t_cmd	*curr_lst_cmd;
	t_cmd	*temp_lst_cmd;

	curr_lst_cmd = *lst_cmd;
	while (curr_lst_cmd)
	{
		temp_lst_cmd = curr_lst_cmd->next;
		i = 0;
		free(curr_lst_cmd->cmd);
		while (curr_lst_cmd->args[i])
		{
			free(curr_lst_cmd->args[i]);
			i++;
		}
		free(curr_lst_cmd->args);
		free(curr_lst_cmd);
		curr_lst_cmd = temp_lst_cmd;
	}
	lst_cmd = NULL;
}

t_cmd	*lst_cmd_last(t_cmd *head)
{
	t_cmd	*current_lst_cmd;
	
	current_lst_cmd = head;
	while (current_lst_cmd->next)
		current_lst_cmd = current_lst_cmd->next;
	return (current_lst_cmd);
}

t_cmd	*build_lst_cmd(char **argv, t_fds *fds, char *file_content, char **path)
{
	size_t			i;
	t_cmd		*lst_cmd;

	i = -1;
	lst_cmd = NULL;
	while (++i < get_cmd_quant(argv))
	{
		if (!compose_cmd(argv[i], &lst_cmd, path))
		{
			clean_path(path);
			clear_all(lst_cmd, fds, file_content);
			exit(EXIT_FAILURE);
		}
	}
	clean_path(path);
	return (lst_cmd);
}
