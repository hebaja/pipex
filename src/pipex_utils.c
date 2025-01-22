#include "../include/pipex.h"

int     do_command(int **fd, t_cmd *lst_cmd, int count)
{
	int     i;
	int     pid;

	i = -1;
	pid = 0;
	pid = fork();
	if (pid < 0)
	{
		perror("Failed to fork processes");
		return (0);
	}
	while (++i < count)
			lst_cmd = lst_cmd->next;
	if (pid == 0)
	{
		dup2(fd[count][0], STDIN_FILENO);
		dup2(fd[count + 1][1], STDOUT_FILENO);
		close_fds(fd, 1);
		execve(lst_cmd->cmd, lst_cmd->args, NULL);
		ft_printf("");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

int	exec_pipex(int **fd, t_cmd **lst_cmd, char *file_content, int out_fd)
{
	int     i;
	int	res;

	i = -1;
	while (++i < 2)
		if(do_command(fd, *lst_cmd, i) == 0)
			break;
	close_fds(fd, 0);
	if (!fetch_file_content(fd, file_content) || !write_to_outfile(fd, out_fd))
	{
		lst_cmd_clear(lst_cmd);
		clear_fd(fd, 3);
		free(file_content);
		return (0);
	}
	lst_cmd_clear(lst_cmd);
	clear_fd(fd, 3);
	free(file_content);
	return (1);
}
