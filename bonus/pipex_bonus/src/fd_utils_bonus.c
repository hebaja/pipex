/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:57:34 by hebatist          #+#    #+#             */
/*   Updated: 2025/01/28 15:27:24 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

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
	out_fd = open(out_filename, O_WRONLY | O_CREAT | O_TRUNC, 0664);
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
	fd = (int **)malloc(sizeof(int *) * (rows + 1));
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
	fd[i] = NULL;
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
