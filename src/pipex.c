#include "../include/pipex.h"

char	*compose_cmd(char *cmd)
{
	char	*paths[] = {"/usr/bin/", "/usr/sbin/"};
	char	*parsed_cmd;
	int	i;

	if (cmd[0] != '/' && access(cmd, F_OK) < 0)
	{
		i = 0;
		while (i < 2)
		{
			parsed_cmd = ft_strjoin(paths[i], cmd);
			if (access(parsed_cmd, F_OK) == 0
			|| access(parsed_cmd, X_OK) == 0)
				return (parsed_cmd);
			free(parsed_cmd);
			i++;
		}
		if (errno == ENOENT)
			ft_printf("command not found: %s\n", cmd);
		else
			ft_printf("%s: %s\n", strerror(errno), cmd);
		return (NULL);
	}
	else
	{
		if (access(cmd, X_OK) < 0)
		{
			ft_printf("%s: %s\n", strerror(errno), cmd);
			return (NULL);
		}
		return (ft_strdup(cmd));
	}
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

/*
int	command_valid(char *command)
{
	if (command[0] != '/')
	{
		if (access(ft_strjoin("/bin/", command), F_OK) < 0 || access(ft_strjoin("/bin/", command), X_OK) < 0)
		{
			perror(command);
			return (0);
		}
	}
	return (1);
}
*/

int	main(int argc, char **argv)
{
	char	*parsed_cmd;

	if (argc == 3)
	{
		if (file_exists(argv[1]))
			ft_printf("%s\n", argv[1]);
		else
			exit(EXIT_FAILURE);

		parsed_cmd = compose_cmd(argv[2]);

		if (parsed_cmd)
		{
			ft_printf("%s\n", parsed_cmd);
			free(parsed_cmd);
		}
		else
			exit(EXIT_FAILURE);
	}

	return (0);
}
