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

int	do_command(int **fd, int input_fd, int output_fd, t_cmd *lst_cmd)
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

int	init_files(char *filename_in, char *filename_out, char **file_content, int *out_fd)
{
	int	res;

	res = 1;
	if (file_exists(filename_in))
	{
		*file_content = (char *)malloc(sizeof(char) * (get_file_len(filename_in) + 1));
		get_file_content(filename_in, *file_content);
	}
	else
		res = 0;
	*out_fd = open(filename_out, O_WRONLY | O_CREAT | O_TRUNC, 0664);	
	if (*out_fd < 0)
		res = 0;
	return (res);
}

// int	init_pipes(int (*fd)[3][2])
// {

// }

/*
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
*/

void	write_to_outfile(int **fd, int out_fd)
{
	int	bytes;
	char	buffer[1024];

	bytes = -1;
	bytes = read(fd[2][0], buffer, sizeof(buffer) -1);
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
}

void	fetch_file_content(int **fd, char *file_content)
{
	write(fd[0][1], file_content, ft_strlen(file_content));
	close(fd[0][1]);
}

void	close_fds(int **fd)
{
	close(fd[0][0]);
	close(fd[1][0]);
	close(fd[1][1]);
	close(fd[2][1]);
}

int	**init_fd(int rows, int cols)
{
	int	**fd;
	int	i;
	int	j;

	i = -1;
	j = -1;
	fd = (int **)malloc(sizeof(int *) * rows);
	if (fd == NULL)
	{
		perror("Failed to allocate memory for fd");
		return (NULL);
	}
	while (++i < rows)
	{
		fd[i] = (int *)malloc(sizeof(int) * 2);
		if (fd[i] == NULL)
		{
			perror("Failed to allocate memory for pipe");
			while (++j < i)
				free(fd[j]);
			free(fd);
			return (NULL);
		}
	}
	return (fd);
}

int	init_pipes(int **fd, int rows)
{
	int	i;

	i = -1;
	while (++i < rows)
	{
		if (pipe(fd[i]) < 0)
		{
			perror("Failed to create pipe");
			return (0);
		}
	}
	return (1);
}

int	main(int argc, char **argv)
{
	// int	fd[3][2];
	int	**fd;
	char	*file_content;
	t_cmd	*lst_cmd1;
	t_cmd	*lst_cmd2;
	int	out_fd;
	int	i;

	i = -1;
	if (argc == 5)
	{
		if (!init_files(argv[1], argv[4], &file_content, &out_fd))
			exit(EXIT_FAILURE);
		lst_cmd1 = compose_cmd(argv[2]);
		lst_cmd2 = compose_cmd(argv[3]);


		// REFACTOR THIS?
		if (lst_cmd1 && lst_cmd2)
		{
			
			fd = init_fd(3, 2);
			if (fd == NULL)
				exit(EXIT_FAILURE);


			if (!init_pipes(fd, 3))
				exit(EXIT_FAILURE);


			do_command(fd, fd[0][0], fd[1][1], lst_cmd1);
			do_command(fd, fd[1][0], fd[2][1], lst_cmd2);

			close_fds(fd);
			
			fetch_file_content(fd, file_content);

			write_to_outfile(fd, out_fd);

			// waitpid(pid1, NULL, 0);
			// waitpid(pid2, NULL, 0);

			cmd_clear(&lst_cmd1);
			cmd_clear(&lst_cmd2);
			free(file_content);
		}
		else
		{	
			perror("Error");
			// Not sure what error throw case any lst_cmd is not built
			exit(EXIT_FAILURE);
		}
	}
	return (0);
}
