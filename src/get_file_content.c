#include "../include/pipex.h"

void	get_file_content(const char *file_name, char *str)
{
	int     fd;
	int	bytes;
	char	*buf;
	int	i;

	fd = open(file_name, O_RDONLY);
	buf = (char *)malloc(sizeof(char) * 10);
	bytes = -1;
	i = 0;
	bytes = read(fd, buf, 10);
	ft_memcpy(str, buf, bytes);
	i += bytes;
	while (bytes)
	{
		bytes = read(fd, buf, 10);
		if (bytes == 0)
			break;
		ft_memcpy(&str[i], buf, bytes);
		i += bytes;
	}
	str[i] = '\0';
	close(fd);
	free(buf);
}
