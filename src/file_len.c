#include "../include/pipex.h"

size_t	file_len(const char *file_name)
{
	int     fd;
	int	bytes;		
	char	*buf;
	size_t	len;

	fd = open(file_name, O_RDONLY);
	buf = (char *)malloc(sizeof(char) * 10);
	bytes = -1;
	bytes = read(fd, buf, 10);
	len = bytes;
	while (bytes)
	{
		bytes = read(fd, buf, 10);
		len += bytes;
	}
	close(fd);
	free(buf);
	return (len);
}
