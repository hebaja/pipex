#include "../include/pipex.h"

char    *add_path(char *cmd)
{
	int	i;
	char	*paths[] = {"/usr/bin/", "/usr/sbin/"};
	char	*built_cmd;
	char	*abs_cmd;

	if (cmd[0] != '/' && access(cmd, F_OK) < 0)
	{
		i = 0;
		while (i < sizeof(paths) / 8)
		{
			built_cmd = ft_strjoin(paths[i++], cmd);
			abs_cmd = ft_substr(built_cmd, 0, cmd_len(built_cmd));
			if (access(abs_cmd, F_OK) == 0 && access(abs_cmd, X_OK) == 0)
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
		if (access(abs_cmd, F_OK) == 0 && access(abs_cmd, X_OK) == 0)
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









t_cmd	*fill_lst_cmd(char *built_cmd, char *cmd, int is_empty)
{
	int     cmd_pos;
	t_cmd   *lst_cmd;

	if (is_empty)
	{
		lst_cmd = (t_cmd *)malloc(sizeof(t_cmd) * 1);
		lst_cmd->cmd = ft_strdup(cmd);
		lst_cmd->args = build_empty_args(cmd);
		lst_cmd->next = NULL;
	}
	else
	{
		cmd_pos = 0;
		lst_cmd = (t_cmd *)malloc(sizeof(t_cmd) * 1);
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
	int     i;
	char    *built_cmd;
	t_cmd	*lst_cmd;

	i = 0;
	if (cmd[i] && !is_empty(cmd))
	{
		while (cmd[i] == ' ' || cmd[i] == '\t')
			i++;
		built_cmd = add_path(&cmd[i]);
		if (access(ft_substr(built_cmd, 0, cmd_len(built_cmd)), F_OK) == 0
		&& access(ft_substr(built_cmd, 0, cmd_len(built_cmd)), X_OK) == 0)
			lst_cmd = fill_lst_cmd(built_cmd, cmd, 0);
		else
		{
			lst_cmd = fill_lst_cmd(built_cmd, cmd, 0);
			if (errno == ENOENT)
				ft_printf("command not found: %s\n", lst_cmd->cmd);
			else
				ft_printf("%s: %s\n", strerror(errno), lst_cmd->cmd);
		}
	}
	else if (is_empty(cmd))
		lst_cmd = fill_lst_cmd(built_cmd, cmd, 1);
	return (lst_cmd);
}





t_cmd   *compose_cmd(char *cmd)
{
	t_cmd   *lst_cmd;
	if (*cmd)
	{
		lst_cmd = cmd_new(cmd);
		return (lst_cmd);
	}
	return (NULL);
}
