#include "../include/pipex.h"

int	main(int argc, char **argv)
{
	char	*file_name;

	(void)argc;

	file_name = argv[1];
	ft_printf("%d %d", file_len(file_name), ft_strlen(file_name));

	// if (argc == 2)
	// {
	// 	int	i = ft_isalpha(argv[1][0]);
	// 	ft_printf("here %d\n", i);
	// 	execve(path, args, NULL);
	// }
	return (0);
}
