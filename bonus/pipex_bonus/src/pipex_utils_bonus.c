/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:00:25 by hebatist          #+#    #+#             */
/*   Updated: 2025/01/28 23:58:43 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	clear_all(t_cmd *head, t_fds *fds, char *file_content)
{
	lst_cmd_clear(&head);
	clear_fds(fds);
	free(file_content);
}

int	fork_error(void)
{
	perror("Failed to fork processes");
	return (0);
}

int	do_command(t_fds *fds, t_cmd *lst_cmd, int count, char *file_content)
{
	int		i;
	int		pid;
	t_cmd	*head;

	i = -1;
	head = lst_cmd;
	pid = fork();
	if (pid < 0)
		return (fork_error());
	while (++i < count)
		lst_cmd = lst_cmd->next;
	if (pid == 0)
	{
		close_unused_fds(fds->cmd_fd, count);
		dup2(fds->cmd_fd[count][0], STDIN_FILENO);
		dup2(fds->cmd_fd[count + 1][1], STDOUT_FILENO);
		close(fds->cmd_fd[count][0]);
		close(fds->cmd_fd[count + 1][1]);
		execve(lst_cmd->cmd, lst_cmd->args, NULL);
		clear_all(head, fds, file_content);
		ft_printf("");
		exit(EXIT_FAILURE);
	}
	lst_cmd->pid = pid;
	return (1);
}

int	exec_pipex(t_fds *fds, t_cmd **lst_cmd, char *file_content, int cmd_quant)
{
	int	i;

	i = -1;
	while (++i < cmd_quant)
		if (do_command(fds, *lst_cmd, i, file_content) == 0)
			break ;
	close_init_fds(fds->cmd_fd, cmd_quant + 1);
	if (!fetch_file_content(fds->cmd_fd, file_content)
		|| !write_to_outfile(fds, lst_cmd, cmd_quant))
	{
		clear_all(*lst_cmd, fds, file_content);
		return (0);
	}
	clear_all(*lst_cmd, fds, file_content);
	return (1);
}
