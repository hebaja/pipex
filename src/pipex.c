#include "../include/pipex.h"

int	main(int argc, char **argv)
{
	char	*file_name;
	char	*file_content;
	size_t	file_len;

	(void)argc;

	file_name = argv[1];
	file_len = get_file_len(file_name);
	file_content = (char *)malloc(sizeof(char) * (file_len));
	get_file_content(file_name, file_content);
	ft_printf("content -> %s\n", file_content);

	//ft_printf("%d", access(file_name, W_OK));

	if (access(file_name, X_OK) < 0)
		perror("Not executable");

	ft_printf("%s", strerror(EBUSY));

	return (0);
}
