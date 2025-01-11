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

char	*add_path(char *cmd)
{
	int	i;
	char	*paths[] = {"/usr/bin/", "/usr/sbin/"};
	char	*built_cmd;
	char	*abs_cmd;

	if (cmd[0] != '/' && access(cmd, F_OK) < 0)
	{
		i = 0;
		while (i < 2)
		{
			built_cmd = ft_strjoin(paths[i], cmd);
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
			built_cmd = NULL;
			abs_cmd = NULL;
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
		free(built_cmd);
		free(abs_cmd);
		built_cmd = NULL;
		abs_cmd = NULL;
	}
	if (errno == ENOENT)
		ft_printf("command not found: %s\n", cmd);
	else
		ft_printf("%s: %s\n", strerror(errno), cmd);
	return (NULL);
}

t_cmd	*cmd_new(char *cmd, char *file_content)
{
	t_cmd	*lst_cmd;
	int	i;
	
	lst_cmd = (t_cmd *)malloc(sizeof(t_cmd) * 1);
	i = 0;
	if (cmd[i])
	{
		while (cmd[i] == ' ' || cmd[i] == '\t')
			i++;
		lst_cmd->cmd = ft_substr(cmd, 0, cmd_len(cmd));




			lst_cmd->args = ft_split(cmd, ' ');
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

t_cmd	*compose_cmd(char *cmd, char *file_content)
{
	t_cmd	*lst_cmd;
	char	*built_cmd;

	built_cmd = add_path(cmd);
	if (built_cmd)
	{
		lst_cmd = cmd_new(built_cmd, file_content);
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
	char	*receive;
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
		lst_cmd1 = compose_cmd(argv[2], file_content);
		lst_cmd2 = compose_cmd(argv[3], NULL);
		ft_printf("%s\n", lst_cmd1->cmd);
		print_args(lst_cmd1->args);
		ft_printf("%s\n", lst_cmd2->cmd);
		print_args(lst_cmd2->args);
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

				// execve(lst_cmd1->cmd[0], char *const *argv, char *const *envp)

				// write(fd[1], file_content, get_file_len(argv[1]) + 1);

				dup2(fd[0], STDIN_FILENO);

				close(fd[0]);
				free(file_content);
				cmd_clear(&lst_cmd1);
				cmd_clear(&lst_cmd2);
				execve(lst_cmd1->cmd, lst_cmd1->args, NULL);
				perror("exeve");
				exit(EXIT_FAILURE);
			}
			else
			{
				receive = (char *)malloc(sizeof(char) * get_file_len(argv[1]) + 1);
				close(fd[0]);
				write(fd[1], receive, get_file_len(argv[1]) + 1);
				close(fd[1]);
				
				// execve(lst_cmd1->cmd, lst_cmd1->args, char *const *envp)

				// dup2(fd2, STDOUT_FILENO);
				// close(fd2)c
				wait(NULL);
				ft_printf("receive -> %s\n", receive);
				// close(fd2);
			}
			cmd_clear(&lst_cmd1);
			cmd_clear(&lst_cmd2);
			ft_printf("receive -> %s", receive);
			free(file_content);
			free(receive);
		}
		else
		{	
			perror("parse");
			exit(EXIT_FAILURE);
		}
	}
	return (0);
}
