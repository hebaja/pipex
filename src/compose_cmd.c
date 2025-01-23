#include "../include/pipex.h"

int	valid_built_cmd(char *built_cmd)
{
	char	*abs_cmd;

	if (!built_cmd)
		return (0);
	abs_cmd = ft_substr(built_cmd, 0, cmd_len(built_cmd));
	if (!abs_cmd)
		return (0);
	if (access(abs_cmd, F_OK) == 0 && access(abs_cmd, X_OK) == 0)
	{
		free(abs_cmd);
		abs_cmd = NULL;
		return (1);
	}
	free(built_cmd);
	free(abs_cmd);
	built_cmd = NULL;
	abs_cmd = NULL;
	return (0);
}

char    *add_path(char *cmd)
{
	size_t	i;
	char	*paths[] = {"/usr/bin/", "/usr/sbin/"};
	char	*built_cmd;

	i = 0;
	while (*cmd == ' ' || *cmd == '\t')
		cmd++;
	if (*cmd != '/' && access(cmd, F_OK) < 0)
	{
		i = 0;
		while (i < sizeof(paths) / 8)
		{
			built_cmd = ft_strjoin(paths[i++], cmd);
			if (!built_cmd)
				return (NULL);
			if (valid_built_cmd(built_cmd))
				return (built_cmd);
		}
	}
	return (ft_strdup(cmd));
}

t_cmd	*fill_lst_cmd(char *built_cmd, char *cmd, int is_empty)
{
	int     cmd_pos;
	t_cmd   *lst_cmd;

	lst_cmd = (t_cmd *)malloc(sizeof(t_cmd) * 1);
	if (!lst_cmd)
		return (NULL);
	if (is_empty)
	{
		lst_cmd->cmd = ft_strdup(cmd);
		lst_cmd->args = build_empty_args(cmd);
		lst_cmd->next = NULL;
	}
	else
	{
		cmd_pos = 0;
		if (!is_path(cmd))
			cmd_pos = command_pos(built_cmd);
		lst_cmd->cmd = ft_substr(built_cmd, 0, cmd_len(built_cmd));
		lst_cmd->args = ft_split(&built_cmd[cmd_pos], ' ');
		lst_cmd->next = NULL;
		free(built_cmd);
	}	
	return (lst_cmd);
}

t_cmd   *cmd_new(char *cmd)
{
	char    *built_cmd;
	char	*abs_cmd;
	t_cmd	*lst_cmd;

	if (*cmd && !is_empty(cmd))
	{
		built_cmd = add_path(cmd);
		if (!built_cmd)
			return (NULL);
		abs_cmd = ft_substr(built_cmd, 0, cmd_len(built_cmd));
		if (access(abs_cmd, F_OK) == 0 && access(abs_cmd, X_OK) == 0)
			lst_cmd = fill_lst_cmd(built_cmd, cmd, 0);
		else
		{
			// lst_cmd = fill_lst_cmd(built_cmd, cmd, 0);
			lst_cmd = NULL;
			free(built_cmd);
			if (errno == ENOENT)
				ft_printf("Command not found: %s\n", cmd);
			else
				ft_printf("%s: %s\n", strerror(errno), cmd);
		}
		free(abs_cmd);
	}
	else if (is_empty(cmd))
		lst_cmd = fill_lst_cmd("", cmd, 1);
	return (lst_cmd);
}

int   compose_cmd(char *cmd, t_cmd **lst_cmd)
{
	t_cmd   *lst_cmd_new;

	if (*lst_cmd == NULL)
	{
		*lst_cmd = cmd_new(cmd);
		if (*lst_cmd)
			return (1);
	}
	else
	{
		lst_cmd_new = cmd_new(cmd);
		if (lst_cmd_new)
		{
			(*lst_cmd)->next = lst_cmd_new;
			return (1);
		}
	}
	return (0);
}
