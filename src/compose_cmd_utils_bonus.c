/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compose_cmd_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 21:04:28 by hebatist          #+#    #+#             */
/*   Updated: 2025/02/04 15:48:19 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	get_args_quant(char const *s)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s == ' ')
			s++;
		if (*s && (*s == 34 || *s == 39))
		{
			count++;
			while (*s && (*s != 34 || *s != 39))
				s++;
		}
		else if (*s && *s != ' ')
			count++;
		while (*s && *s != ' ')
			s++;
	}
	return (count);
}

int	put_args(char **args, char *cmd, int len)
{
	int			i;

	i = 1;
	if (quote_quant(catch_quote(cmd), cmd) % 2 != 0)
		return (0);
	args[0] = ft_substr(cmd, 0, cmd_len(cmd));
	while (i < len && *cmd)
	{
		while (*cmd != ' ')
			cmd++;
		cmd++;
		if (*cmd == 34 || *cmd == 39)
		{
			args[i] = remove_quotes(*cmd, cmd);
			cmd++;
			while (*cmd && *cmd != catch_quote(cmd))
				cmd++;
		}
		else
			args[i] = catch_option(cmd);
		cmd++;
		i++;
	}
	args[i] = NULL;
	return (1);
}

char	**fill_args(char *cmd)
{
	int			len;
	char		**args;

	len = get_args_quant(cmd);
	args = (char **)malloc(sizeof(char *) * (len + 1));
	if (args == NULL)
		return (NULL);
	if (!put_args(args, cmd, len))
	{
		free(args);
		return (NULL);
	}
	return (args);
}

t_cmd	*fill_non_empty_cmd(char *built_cmd, char *cmd)
{
	t_cmd		*lst_cmd;

	lst_cmd = (t_cmd *)malloc(sizeof(t_cmd) * 1);
	if (lst_cmd == NULL)
		return (NULL);
	lst_cmd->cmd = ft_substr(built_cmd, 0, cmd_len(built_cmd));
	lst_cmd->args = fill_args(cmd);
	if (lst_cmd->args == NULL)
	{
		ft_printf("%s: %s\n", lst_cmd->cmd, strerror(ENOEXEC));
		free(lst_cmd->cmd);
		free(lst_cmd);
		return (NULL);
	}
	lst_cmd->next = NULL;
	lst_cmd->pid = 0;
	return (lst_cmd);
}

t_cmd	*fill_empty_cmd(char *cmd)
{
	t_cmd	*lst_cmd;

	lst_cmd = (t_cmd *)malloc(sizeof(t_cmd) * 1);
	if (lst_cmd == NULL)
		return (NULL);
	lst_cmd->cmd = ft_strdup(cmd);
	lst_cmd->args = build_empty_args(cmd);
	lst_cmd->next = NULL;
	lst_cmd->pid = 0;
	return (lst_cmd);
}
