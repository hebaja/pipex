#include "../include/pipex.h"

int	main(int argc, char **argv)
{
	char	*file_name;
	char	*file_content;
	size_t	file_len;

	int	fd[2];
	int	pid;

	(void)argc;

	file_name = argv[1];
	file_len = get_file_len(file_name);
	file_content = (char *)malloc(sizeof(char) * (file_len));
	get_file_content(file_name, file_content);
	ft_printf("content -> %s\n", file_content);

	if (pipe(fd) < 0)
	{
		perror("pipe");
		exit(0);
	}
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);

	}

	


	return (0);
}
