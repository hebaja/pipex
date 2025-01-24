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

#include "../include/pipex.h"

void	get_file_content(const char *file_name, char *str)
{
	int			fd;
	int			bytes;
	int			i;
	char		*buf;

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
			break ;
		ft_memcpy(&str[i], buf, bytes);
		i += bytes;
	}
	str[i] = '\0';
	close(fd);
	free(buf);
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
