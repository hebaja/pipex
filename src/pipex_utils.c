/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:00:25 by hebatist          #+#    #+#             */
/*   Updated: 2025/01/23 22:53:49 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	clear_all(t_cmd *head, int **fd, char *file_content)
{
	lst_cmd_clear(&head);
	clear_fd(fd, 3);
	free(file_content);
}

int	fork_error(void)
{
	perror("Failed to fork processes");
	return (0);
}

int	do_command(int **fd, t_cmd *lst_cmd, int count, char *file_content)
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
		close_unused_fds(fd, count);
		dup2(fd[count][0], STDIN_FILENO);
		dup2(fd[count + 1][1], STDOUT_FILENO);
		close(fd[count][0]);
		close(fd[count + 1][1]);
		execve(lst_cmd->cmd, lst_cmd->args, NULL);
		clear_all(head, fd, file_content);
		ft_printf("");
		exit(EXIT_FAILURE);
	}
	lst_cmd->pid = pid;
	return (1);
}

int	exec_pipex(int **fd, t_cmd **lst_cmd, char *file_content, int out_fd)
{
	int	i;

	i = -1;
	while (++i < 2)
		if (do_command(fd, *lst_cmd, i, file_content) == 0)
			break ;
	close_fds(fd, 3);
	if (!fetch_file_content(fd, file_content)
		|| !write_to_outfile(fd, out_fd, lst_cmd))
	{
		clear_all(*lst_cmd, fd, file_content);
		return (0);
	}
	lst_cmd_clear(lst_cmd);
	clear_fd(fd, 3);
	free(file_content);
	return (1);
}
