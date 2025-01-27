/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_content_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:57:44 by hebatist          #+#    #+#             */
/*   Updated: 2025/01/23 22:38:43 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	write_to_file_content(const char *in_filename, char *buffer, char *file_content)
{
	int			fd;
	int			i;
	int			bytes;
	
	i = 0;
	fd = open(in_filename, O_RDONLY);
	bytes = read(fd, buffer, 10);
	if (bytes == -1)
		return (0);
	ft_memcpy(file_content, buffer, bytes);
	i += bytes;
	while (bytes)
	{
		bytes = read(fd, buffer, 10);
		if (bytes == -1)
			return (0);
		if (bytes == 0)
			break ;
		ft_memcpy(&file_content[i], buffer, bytes);
		i += bytes;
	}
	file_content[i] = '\0';
	close(fd);
	free(buffer);
	return (1);
}

char	*get_file_content(const char *in_filename)
{
	char		*buffer;
	char		*file_content;

	file_content = (char *)malloc(sizeof(char) * (get_file_len(in_filename) + 1));
	buffer = (char *)malloc(sizeof(char) * 10);
	if (file_content && buffer)
	{
		if(write_to_file_content(in_filename, buffer, file_content))
			return (file_content);
		else
			return (NULL);
	}
	return (NULL);
}

size_t	get_file_len(const char *file_name)
{
	int			fd;
	int			bytes;
	char		*buf;
	size_t		len;

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
