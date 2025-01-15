#include "../include/pipex.h"
#include <complex.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void	cmd_clear(t_cmd **lst_cmd)
{
	int	i;

	i = 0;
	free((*lst_cmd)->cmd);
	while((*lst_cmd)->args[i])
	{
		free((*lst_cmd)->args[i]);
		i++;
	}
	free((*lst_cmd)->args);
	free(*lst_cmd);
	*lst_cmd = NULL;
}

int	file_exists(char *file_name)
{
	if (access(file_name, F_OK) < 0)
	{
		perror(file_name);
		return (0);
	}
	return (1);
}

void	print_args(char **args)
{
	while (*args)
	{
		ft_printf("%s\n", *args);
		args++;
	}
}

int	do_command(int fd[2][2], int input_fd, int output_fd, t_cmd *lst_cmd)
{
	int	pid;

	pid = 0;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		dup2(input_fd, STDIN_FILENO);
		dup2(output_fd, STDOUT_FILENO);
		close(fd[0][1]);
		close(fd[1][0]);
		close(fd[0][0]);
		close(fd[1][1]);
		execve(lst_cmd->cmd, lst_cmd->args, NULL);
		ft_printf("");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

int	main(int argc, char **argv)
{
	int	fd[3][2];
	char	*file_content;
	t_cmd	*lst_cmd1;
	t_cmd	*lst_cmd2;
	int	fd2;
	char	buffer[1024];
	int	bytes;
	int	i;

	fd2 = open("outfile", O_WRONLY | O_CREAT | O_TRUNC, 0664);	
	i = -1;
	if (argc == 5)
	{
		if (file_exists(argv[1]))
		{
			file_content = (char *)malloc(sizeof(char) * (get_file_len(argv[1]) + 1));
			get_file_content("infile", file_content);
		}
		else
			exit(EXIT_FAILURE);
		lst_cmd1 = compose_cmd(argv[2]);
		if (lst_cmd1)
		{
			ft_printf("%s\n", lst_cmd1->cmd);
			print_args(lst_cmd1->args);
		}
		else
		{
			free(file_content);
			exit(EXIT_FAILURE);
		}
		lst_cmd2 = compose_cmd(argv[3]);
		if (lst_cmd2)
		{
			ft_printf("%s\n", lst_cmd2->cmd);
			print_args(lst_cmd2->args);
		}
		if (lst_cmd1 && !is_empty(lst_cmd1->cmd))
		{
			while (++i < 3)
			{
				if (pipe(fd[i]) < 0)
				{
					perror("pipe");
					exit(EXIT_FAILURE);
				}
			}

			

			int pid1 = do_command(fd, fd[0][0], fd[1][1], lst_cmd1);
			int pid2 = do_command(fd, fd[1][0], fd[2][1], lst_cmd2);

			bytes = -1;

			close(fd[0][0]);
			close(fd[1][0]);
			close(fd[1][1]);
			close(fd[2][1]);
			write(fd[0][1], file_content, ft_strlen(file_content));
			close(fd[0][1]);

			bytes = read(fd[2][0], buffer, sizeof(buffer) -1);
			close(fd[2][0]);
			dup2(fd2, STDOUT_FILENO);
			close(fd2);
			if (bytes > 0)
			{
				buffer[bytes] = '\0';
				ft_printf("%s", buffer);
			}
			else
			{
				ft_printf("");
			}

			waitpid(pid1, NULL, 0);
			waitpid(pid2, NULL, 0);

			cmd_clear(&lst_cmd1);
			cmd_clear(&lst_cmd2);
			free(file_content);
		}
		else
		{	
			perror("parse");
			exit(EXIT_FAILURE);
		}
	}
	return (0);
}
