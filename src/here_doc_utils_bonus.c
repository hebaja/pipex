/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 11:52:11 by hebatist          #+#    #+#             */
/*   Updated: 2025/02/01 11:52:37 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	case_error(int fd, char *limit)
{
	close(fd);
	free(limit);
	exit(EXIT_FAILURE);
}

void	clean(int fd, char *str, char *limit)
{
	close(fd);
	free(str);
	free(limit);
}

void	init_here_doc(char **argv, char **path)
{
	int			fd;
	char		*str;
	char		*limit;

	limit = ft_strjoin(argv[2], "\n");
	fd = open("tempfile", O_WRONLY | O_CREAT | O_TRUNC, 0664);
	ft_printf("here_doc> ");
	str = get_next_line(0);
	if (str == NULL)
		case_error(fd, limit);
	while (strcmp(str, limit) != 0)
	{
		ft_printf("here_doc> ");
		write(fd, str, ft_strlen(str));
		free(str);
		str = get_next_line(0);
		if (str == NULL)
			case_error(fd, limit);
	}
	clean(fd, str, limit);
	if (access("tempfile", F_OK) < 0 && access("tempfile", R_OK) < 0)
		perror("Could not access file");
	else
		init_pipex("tempfile", &argv[3], path);
	unlink("tempfile");
}
