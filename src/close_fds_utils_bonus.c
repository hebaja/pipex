/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 11:33:33 by hebatist          #+#    #+#             */
/*   Updated: 2025/02/01 11:33:36 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	clear_fds(t_fds *fds)
{
	int	i;

	i = -1;
	while (++i < fds->cmd_fd_rows)
		free(fds->cmd_fd[i]);
	free(fds->cmd_fd);
	free(fds);
	fds = NULL;
}

void	close_init_fds(t_fds *fds, int size)
{
	int	i;
	int	j;

	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < 2)
		{
			if (i == 0)
			{
				if (j == 0)
					close(fds->cmd_fd[i][j]);
			}
			else if (i == (size - 1))
			{
				if (j == 1)
					close(fds->cmd_fd[i][j]);
			}
			else
				close(fds->cmd_fd[i][j]);
		}
	}
}

void	close_unused_fds(t_fds *fds, int count)
{
	int	i;
	int	j;

	i = -1;
	while (fds->cmd_fd[++i])
	{
		j = -1;
		while (++j < 2)
		{
			if (i == count)
			{
				if (j == 1)
					close(fds->cmd_fd[i][j]);
			}
			else if (i == count + 1)
			{
				if (j == 0)
					close(fds->cmd_fd[i][j]);
			}
			else
				close(fds->cmd_fd[i][j]);
		}
	}
}
