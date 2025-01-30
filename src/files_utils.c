/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:58:20 by hebatist          #+#    #+#             */
/*   Updated: 2025/01/29 21:34:05 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	file_exists(char *file_name)
{
	if (access(file_name, F_OK) < 0)
	{
		perror(file_name);
		return (0);
	}
	return (1);
}

int	init_files(char *fname_in, char *fname_out, char **fcontent, int *fd)
{
	int	res;

	res = 1;
	if (file_exists(fname_in))
	{
		*fcontent = (char *)malloc(sizeof(char) * (get_file_len(fname_in) + 1));
		if (!fcontent)
		{
			perror(fname_in);
			res = 0;
		}
		else
			get_file_content(fname_in, *fcontent);
	}
	else
		res = 0;
	*fd = open(fname_out, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (*fd < 0)
		res = 0;
	return (res);
}

void	wait_for_pids(t_cmd *lst_cmd)
{
	int	status;

	while (lst_cmd)
	{
		waitpid(lst_cmd->pid, &status, 0);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) != 0)
			{
				if (errno != ENOENT && status != 256)
					perror("Coud not execute command");
			}
		}
		lst_cmd = lst_cmd->next;
	}
}

int	write_to_outfile(int **fd, int out_fd, t_cmd **lst_cmd)
{
	int			bytes;
	char		buffer[1024];

	bytes = -1;
	wait_for_pids(*lst_cmd);
	bytes = read(fd[2][0], buffer, sizeof(buffer));
	if (bytes == -1)
	{
		perror("Error writing to file");
		return (0);
	}
	close(fd[2][0]);
	dup2(out_fd, STDOUT_FILENO);
	close(out_fd);
	if (bytes > 0)
	{
		buffer[bytes] = '\0';
		ft_printf("%s", buffer);
	}
	else
		ft_printf("");
	return (1);
}

int	fetch_file_content(int **fd, char *file_content)
{
	int	bytes;

	bytes = write(fd[0][1], file_content, ft_strlen(file_content));
	close(fd[0][1]);
	if (bytes < 0)
	{
		perror("Error reading from file");
		return (0);
	}
	else
		return (1);
}
