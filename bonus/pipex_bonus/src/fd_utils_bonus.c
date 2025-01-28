/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:57:34 by hebatist          #+#    #+#             */
/*   Updated: 2025/01/27 22:04:32 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void    close_init_fds(int **fd, int size)
{
	int     i;
	int     j;

	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < 2)
		{
			if (i == 0)
			{
				if (j == 0)
					close(fd[i][j]);
			}
			else if (i == (size - 1))
			{
				if (j == 1)
					close(fd[i][j]);
			}
			else
				close(fd[i][j]);
		}
	}
}

void    close_unused_fds(int **fd, int count)
{
	int     i;
	int     j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 2)
		{
			if (i == count)
			{
				if (j == 1)
					close(fd[i][j]);
			}
			else if (i == count + 1)
			{
				if (j == 0)
					close(fd[i][j]);
			}
			else
				close(fd[i][j]);
		}
	}
}

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

void	fd_alloc_fail(void)
{
	perror("Failed to allocate memory for fd");
	exit(EXIT_FAILURE);
}

t_fds	*build_t_fds(int **fd, int rows, char *out_filename)
{
	t_fds	*fds;
	int	out_fd;

	fds = (t_fds *)malloc(sizeof(t_fds) * 1);
	out_fd = open(out_filename, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (fds == NULL || out_fd < 0)
		return (NULL);
	fds->cmd_fd = fd;
	fds->cmd_fd_rows = rows;
	fds->out_fd = out_fd;
	return (fds);
}

t_fds	*init_t_fds(int rows, char *out_filename)
{
	int	**fd;
	int	i;
	int	j;

	i = -1;
	j = -1;
	fd = (int **)malloc(sizeof(int *) * rows);
	if (fd == NULL)
		fd_alloc_fail();
	while (++i < rows)
	{
		fd[i] = (int *)malloc(sizeof(int) * 2);
		if (fd[i] == NULL)
		{
			while (++j < i)
				free(fd[j]);
			free(fd);
			fd_alloc_fail();
		}
	}
	return (build_t_fds(fd, rows, out_filename));
}

int	init_pipes(t_fds *fds)
{
	int	i;

	i = -1;
	while (++i < fds->cmd_fd_rows)
	{
		if (pipe(fds->cmd_fd[i]) < 0)
		{
			perror("Failed to create pipe");
			return (0);
		}
	}
	return (1);
}
