/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:57:34 by hebatist          #+#    #+#             */
/*   Updated: 2025/01/23 19:13:33 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	close_fds(int **fd, int size)
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

void	clear_fd(int **fd, int rows)
{
	int	i;

	i = -1;
	while (++i < rows)
		free(fd[i]);
	free(fd);
	fd = NULL;
}

int	**init_fd(int rows)
{
	int	**fd;
	int	i;
	int	j;

	i = -1;
	j = -1;
	fd = (int **)malloc(sizeof(int *) * rows);
	if (fd == NULL)
	{
		perror("Failed to allocate memory for fd");
		exit(EXIT_FAILURE);
	}
	while (++i < rows)
	{
		fd[i] = (int *)malloc(sizeof(int) * 2);
		if (fd[i] == NULL)
		{
			perror("Failed to allocate memory for pipe");
			while (++j < i)
				free(fd[j]);
			free(fd);
			exit(EXIT_FAILURE);
		}
	}
	return (fd);
}

int	init_pipes(int **fd, int rows)
{
	int	i;

	i = -1;
	while (++i < rows)
	{
		if (pipe(fd[i]) < 0)
		{
			perror("Failed to create pipe");
			return (0);
		}
	}
	return (1);
}
