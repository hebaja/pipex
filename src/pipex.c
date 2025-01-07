#include "../include/pipex.h"

size_t	get_file_len(char *file_name)
{
        int     fd;
	int	bytes;		
        char    *buf;
	size_t	len;
	
	fd = open(file_name, O_RDONLY);
	buf = (char *)malloc(sizeof(char) * 10);
        bytes = -1;
        bytes = read(fd, buf, 10);
        buf[bytes] = 0;
	len = bytes;
        while(bytes)
        {
                bytes = read(fd, buf, 10);
		len += bytes;
        }
        close(fd);
	free(buf);
	return (len);
}

int	main(int argc, char **argv)
{
	char	*file_name;

	(void)argc;

	file_name = argv[1];
	ft_printf("%d %d", get_file_len(file_name), ft_strlen(file_name));

	// if (argc == 2)
	// {
	// 	int	i = ft_isalpha(argv[1][0]);
	// 	ft_printf("here %d\n", i);
	// 	execve(path, args, NULL);
	// }
	return (0);
}
