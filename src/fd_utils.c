#include "../include/pipex.h"

void    close_fds(int **fd, int all)
{
	close(fd[0][0]);
	close(fd[1][0]);
	close(fd[1][1]);
	close(fd[2][1]);
	if (all)
	{
		close(fd[0][1]);
		close(fd[2][0]);
	}
}

void    clear_fd(int **fd, int rows)
{
	int     i;

	i = -1;
	while (++i < rows)
		free(fd[i]);
	free(fd);
	fd = NULL;
}

int     **init_fd(int rows, int cols)
{
	int     **fd;
	int     i;
	int     j;

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

int     init_pipes(int **fd, int rows)
{
	int     i;

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
