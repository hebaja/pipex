#include "../include/pipex.h"

void    lst_cmd_clear(t_cmd **lst_cmd)
{
	int     i;
	t_cmd   *curr_lst_cmd;
	t_cmd   *temp_lst_cmd;

	curr_lst_cmd = *lst_cmd;
	while (curr_lst_cmd)
	{
		temp_lst_cmd = curr_lst_cmd->next;
		i = 0;
		free(curr_lst_cmd->cmd);
		while(curr_lst_cmd->args[i])
		{
			free(curr_lst_cmd->args[i]);
			i++;
		}
		free(curr_lst_cmd->args);
		free(curr_lst_cmd);
		curr_lst_cmd = temp_lst_cmd;
	}
	lst_cmd = NULL;
}

void    print_args(char **args)
{
	while (*args)
	{
		ft_printf("%s\n", *args);
		args++;
	}
}
