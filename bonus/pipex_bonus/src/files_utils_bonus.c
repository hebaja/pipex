/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:58:20 by hebatist          #+#    #+#             */
/*   Updated: 2025/01/23 22:44:55 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	file_exists(char *file_name)
{
	if (access(file_name, F_OK) < 0)
	{
		perror(file_name);
		return (0);
	}
	return (1);
}

char	*init_infile_content(char *in_filename)
{
	char	*file_content;

	file_content = NULL;
	if (file_exists(in_filename))
		file_content = get_file_content(in_filename);
	else
		perror(in_filename);	
	return (file_content);
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
				if (errno != ENOENT)
					perror("Execve failed");
			}
		}
		lst_cmd = lst_cmd->next;
	}
}

int	write_to_outfile(t_fds *fds, t_cmd **lst_cmd, int cmd_quant)
{
	int			bytes;
	char		buffer[1024];

	bytes = -1;
	wait_for_pids(*lst_cmd);
	bytes = read(fds->cmd_fd[cmd_quant][0], buffer, sizeof(buffer));
	if (bytes == -1)
	{
		perror("Error writing to file");
		return (0);
	}
	close(fds->cmd_fd[cmd_quant][0]);
	dup2(fds->out_fd, STDOUT_FILENO);
	close(fds->out_fd);
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
