/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compose_cmd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 21:04:28 by hebatist          #+#    #+#             */
/*   Updated: 2025/01/30 00:01:58 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*catch_option(char *str)
{
	char		*str_new;
	int			i;
	int			len;

	i = 0;
	len = 0;
	while (str[len] && str[len] != ' ')
		len++;
	str_new = (char *)malloc(sizeof(char) * (len + 1));
	while (*str != ' ')
	{
		str_new[i] = *str;
		str++;
		i++;
	}
	str_new[i] = '\0';
	return (str_new);
}

char	**fill_complex_args(char *cmd)
{
	int			len;
	int			i;
	char		**args;

	len = options_quant(cmd) + 3;
	i = 1;
	args = (char **)malloc(sizeof(char *) * (len + 1));
	args[0] = ft_substr(cmd, 0, cmd_len(cmd));
	while (i < len - 2)
	{
		while (*cmd != '-')
			cmd++;
		args[i] = catch_option(cmd);
		i++;
	}
	args[i] = remove_quotes(ft_strchr(cmd, 39));
	args[++i] = NULL;
	return (args);
}

char	**fill_simple_args(char *cmd)
{
	char		**args;

	args = (char **)malloc(sizeof(char *) * 3);
	args[0] = ft_substr(cmd, 0, cmd_len(cmd));
	args[1] = remove_quotes(ft_strchr(cmd, 39));
	args[2] = NULL;
	return (args);
}

t_cmd	*fill_non_empty_cmd(char *built_cmd, char *cmd)
{
	t_cmd		*lst_cmd;
	int			cmd_pos;

	cmd_pos = 0;
	lst_cmd = (t_cmd *)malloc(sizeof(t_cmd) * 1);
	if (lst_cmd == NULL)
		return (NULL);
	if (!is_path(cmd))
		cmd_pos = command_pos(built_cmd);
	lst_cmd->cmd = ft_substr(built_cmd, 0, cmd_len(built_cmd));
	if (contains_quote(cmd) && options_quant(cmd))
		lst_cmd->args = fill_complex_args(cmd);
	else if (contains_quote(cmd))
		lst_cmd->args = fill_simple_args(cmd);
	else
		lst_cmd->args = ft_split(&built_cmd[cmd_pos], ' ');
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
