#include "../include/pipex.h"
#include <complex.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

size_t	cmd_len(char *cmd)
{
	size_t	count;

	count = 0;
	if (*cmd)
	{
		while(*cmd == ' ' || *cmd == '\t')
			cmd++;
		while(*cmd && (*cmd != ' ' && *cmd != '\t'))
		{
			count++;
			cmd++;
		}
	}
	return (count);
}

int	is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	is_path(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	command_pos(char *str)
{
	int	i;
	int	last;

	i = 0;
	last = 0;
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '/')
			last = i + 1;
		i++;
	}
	return (last);
}

char	*add_path(char *cmd)
{
	int	i;
	char	*paths[] = {"/usr/bin/", "/usr/sbin/"};
	char	*built_cmd;
	char	*abs_cmd;
	char	*received_cmd;

	if (cmd[0] != '/' && access(cmd, F_OK) < 0)
	{
		i = 0;
		while (i < 2)
		{
			built_cmd = ft_strjoin(paths[i++], cmd);
			abs_cmd = ft_substr(built_cmd, 0, cmd_len(built_cmd));
			if (access(abs_cmd, F_OK) == 0
			&& access(abs_cmd, X_OK) == 0)
			{
				free(abs_cmd);
				abs_cmd = NULL;
				return (built_cmd);
			}
			free(built_cmd);
			free(abs_cmd);
		}
	}
	else
	{
		built_cmd = ft_strdup(cmd);
		abs_cmd = ft_substr(built_cmd, 0, cmd_len(built_cmd));
		if (access(abs_cmd, F_OK) == 0
		&& access(abs_cmd, X_OK) == 0)
		{
			free(abs_cmd);
			abs_cmd = NULL;
			return (built_cmd);
		}
		free(built_cmd);
		free(abs_cmd);
	}
	built_cmd = NULL;
	abs_cmd = NULL;
	return (ft_strdup(cmd));
}

char	**build_empty_args(char *empty_str)
{
	char	**empty_args;
	char	*empty_arg;

	empty_args = (char **)malloc(sizeof(char *) * 2);
	if (!empty_args)
		return (NULL);
	empty_args[0] = ft_strdup(empty_str);
	empty_args[1] = NULL;
 	return (empty_args);
}

t_cmd	*cmd_new(char *cmd)
{
	t_cmd	*lst_cmd;
	int	i;
	int	cmd_pos;
	char	*built_cmd;
	
	i = 0;
	cmd_pos = 0;
	if (cmd[i] && !is_empty(cmd))
	{
		lst_cmd = (t_cmd *)malloc(sizeof(t_cmd) * 1);
		while (cmd[i] == ' ' || cmd[i] == '\t')
			i++;

		built_cmd = add_path(&cmd[i]);
		if (access(ft_substr(built_cmd, 0, cmd_len(built_cmd)), F_OK) == 0
		&& access(ft_substr(built_cmd, 0, cmd_len(built_cmd)), X_OK) == 0)
		{
			if (!is_path(cmd))
				cmd_pos = command_pos(built_cmd);
			lst_cmd->cmd = ft_substr(built_cmd, 0, cmd_len(built_cmd));
			lst_cmd->args = ft_split(&built_cmd[cmd_pos], ' ');
			lst_cmd->next = NULL;
			free(built_cmd);
		}
		else
		{
			/*
			lst_cmd->cmd = ft_strdup("");
			lst_cmd->args = build_empty_args("");
			lst_cmd->next = NULL;
			*/
			if (!is_path(cmd))
				cmd_pos = command_pos(built_cmd);
			lst_cmd->cmd = ft_substr(built_cmd, 0, cmd_len(built_cmd));
			lst_cmd->args = ft_split(&built_cmd[cmd_pos], ' ');
			lst_cmd->next = NULL;
			
			free(built_cmd);

			if (errno == ENOENT)
				ft_printf("command not found: %s\n", lst_cmd->cmd);
			else
				ft_printf("%s: %s\n", strerror(errno), lst_cmd->cmd);

			perror("cmd_new");
		}
	}
	else if (is_empty(cmd))
	{		
		lst_cmd = (t_cmd *)malloc(sizeof(t_cmd) * 1);
		lst_cmd->cmd = ft_strdup(cmd);
		lst_cmd->args = build_empty_args(cmd);
		lst_cmd->next = NULL;
	}
	return (lst_cmd);
}

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

t_cmd	*compose_cmd(char *cmd)
{
	t_cmd	*lst_cmd;
	if (*cmd)
	{
		lst_cmd = cmd_new(cmd);
		return (lst_cmd);
	}
	return (NULL);
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

	fd2 = open("outfile", O_WRONLY | O_CREAT, 0664);	
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
				ft_printf("\0");
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
