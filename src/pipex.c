#include "../include/pipex.h"
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
			|| access(abs_cmd, X_OK) == 0)
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
		|| access(abs_cmd, X_OK) == 0)
		{
			free(abs_cmd);
			abs_cmd = NULL;
			return (built_cmd);
		}
	}
	received_cmd = ft_substr(cmd, 0, cmd_len(cmd));
	if (errno == ENOENT)
		ft_printf("command not found: %s\n", received_cmd);
	else
		ft_printf("%s: %s\n", strerror(errno), received_cmd);
	//free(built_cmd);
	//free(abs_cmd);
	free(received_cmd);
	built_cmd = NULL;
	abs_cmd = NULL;
	received_cmd = NULL;
	return (NULL);
}

t_cmd	*cmd_new(char *cmd)
{
	t_cmd	*lst_cmd;
	int	i;
	int	cmd_pos;
	
	lst_cmd = (t_cmd *)malloc(sizeof(t_cmd) * 1);
	i = 0;
	cmd_pos = 0;
	if (cmd[i])
	{
		while (cmd[i] == ' ' || cmd[i] == '\t')
			i++;

		cmd_pos = command_pos(cmd);

		// Maybe, verify if there is path and implement add_path here, case it is needed.

		lst_cmd->cmd = ft_substr(cmd, 0, cmd_len(cmd));
		lst_cmd->args = ft_split(&cmd[cmd_pos], ' ');
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
	char	*built_cmd;

	built_cmd = add_path(cmd);
	if (built_cmd)
	{
		lst_cmd = cmd_new(built_cmd);
		free(built_cmd);
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

int	main(int argc, char **argv)
{
	int	fd[2];
	int	pid;
	char	*file_content;
	t_cmd	*lst_cmd1;
	t_cmd	*lst_cmd2;
	int	fd2;

	fd2 = open("outfile", O_WRONLY | O_CREAT, 0664);	

	if (argc == 4)
	{
		if (file_exists(argv[1]))
		{
			file_content = (char *)malloc(sizeof(char) * (get_file_len(argv[1]) + 1));
			get_file_content("infile", file_content);
		 	// ft_printf("%s\n", content);

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
			//cmd_clear(&lst_cmd1);
			free(file_content);
			exit(EXIT_FAILURE);
		}
		lst_cmd2 = compose_cmd(argv[3]);
		if (lst_cmd2)
		{
			ft_printf("%s\n", lst_cmd2->cmd);
			print_args(lst_cmd2->args);
		}
		if (lst_cmd1)
		{
			if (pipe(fd) < 0)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
			pid = fork();
			if (pid == 0)
			{
				close(fd[1]);
				dup2(fd[0], STDIN_FILENO);
				close(fd[0]);
				//free(file_content);
				//cmd_clear(&lst_cmd1);
				//cmd_clear(&lst_cmd2);
				execve(lst_cmd1->cmd, lst_cmd1->args, NULL);
				perror("exeve");
				exit(EXIT_FAILURE);
			}
			else
			{
				close(fd[0]);
				write(fd[1], file_content, ft_strlen(file_content));
				close(fd[1]);
				wait(NULL);
			}
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
