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

void	print_here_doc(char **argv)
{
	int	len;

	len = 0;
	while (argv[len])
		len++;
	len -= 5;
	while (len--)
		ft_printf("pipe ");
	ft_printf("here_doc> ");
}

void	init_here_doc(char **argv, char **path)
{
	int			fd;
	char		*str;
	char		*limit;

	limit = ft_strjoin(argv[2], "\n");
	fd = open("tempfile", O_WRONLY | O_CREAT | O_TRUNC, 0664);
	print_here_doc(argv);
	str = get_next_line(0);
	if (str == NULL)
		case_error(fd, limit);
	while (ft_strncmp(str, limit, ft_strlen(str)) != 0)
	{
		print_here_doc(argv);
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
