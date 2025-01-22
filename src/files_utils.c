#include "../include/pipex.h"

int     file_exists(char *file_name)
{
	if (access(file_name, F_OK) < 0)
	{
		perror(file_name);
		return (0);
	}
	return (1);
}

int	init_files(char *filename_in, char *filename_out, char **file_content, int *out_fd)
{
	int     res;

	res = 1;
	if (file_exists(filename_in))
	{
		*file_content = (char *)malloc(sizeof(char) * (get_file_len(filename_in) + 1));
		if (!file_content)
			res = 0;
		else
			get_file_content(filename_in, *file_content);
	}
	else
		res = 0;
	*out_fd = open(filename_out, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (*out_fd < 0)
		res = 0;
	return (res);
}

int	write_to_outfile(int **fd, int out_fd)
{
	int     bytes;
	char    buffer[1024];

	bytes = -1;
	bytes = read(fd[2][0], buffer, sizeof(buffer));
	if (bytes == -1)
	{
		perror("Error writing to file");
		return (0);
	}
	close(fd[2][0]);
	dup2(out_fd, STDOUT_FILENO);
	close(out_fd);
	if (bytes > 0)
	{
		buffer[bytes] = '\0';
		ft_printf("%s", buffer);
	}
	else
		ft_printf("");
	return (1);
}

int	fetch_file_content(int **fd, char *file_content)
{
	int	bytes;

	bytes = write(fd[0][1], file_content, ft_strlen(file_content));
	close(fd[0][1]);

	if (bytes < 0)
	{
		perror("Error reading from file");
		return (0);
	}
	else
		return (1);
}
