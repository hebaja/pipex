/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 00:09:25 by hebatist          #+#    #+#             */
/*   Updated: 2025/01/24 17:44:42 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include "../include/get_next_line.h"

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*ptr;
	int		i;
	int		len1;
	int		len2;

	i = -1;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	ptr = (char *)malloc(len1 + len2 + 1);
	if (ptr == NULL)
		return (NULL);
	while (++i < len1)
		ptr[i] = s1[i];
	i--;
	while (++i < len1 + len2)
		ptr[i] = s2[i - len1];
	ptr[i] = '\0';
	free(s1);
	return (ptr);
}

char	*store_rest(char *line)
{
	char	*rest;
	char	*temp;

	if (line == NULL || *line == '\0')
		return (NULL);
	temp = ft_strchr(line, '\n');
	if (!temp)
		return (NULL);
	rest = ft_strdup(++temp);
	if (*rest == '\0')
	{
		free(rest);
		rest = NULL;
	}
	*temp = '\0';
	return (rest);
}

void	*invalid_fd(char *buf, char *line)
{
	free(buf);
	free(line);
	return (NULL);
}

char	*fill_line(int fd, char *line)
{
	char	*buf;
	int		bytes;

	bytes = 1;
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	while (bytes > 0)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes == -1)
			return (invalid_fd(buf, line));
		else if (bytes == 0)
			break ;
		if (!line)
			line = ft_strdup("");
		buf[bytes] = '\0';
		line = gnl_strjoin(line, buf);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(buf);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*rest[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = fill_line(fd, rest[fd]);
	if (!line)
	{
		free(rest[fd]);
		rest[fd] = NULL;
		return (NULL);
	}
	rest[fd] = store_rest(line);
	return (line);
}
