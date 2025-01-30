/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compose_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:57:23 by hebatist          #+#    #+#             */
/*   Updated: 2025/01/30 00:01:08 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*add_path(char *cmd)
{
	size_t	i;
	char	**paths;
	char	*built_cmd;

	while (*cmd == ' ' || *cmd == '\t')
		cmd++;
	if (*cmd != '/' && access(cmd, F_OK) < 0)
	{
		i = 0;
		paths = build_paths();
		while (paths[i])
		{
			built_cmd = ft_strjoin(paths[i++], cmd);
			if (built_cmd && valid_built_cmd(built_cmd))
			{
				clean_paths(paths);
				return (built_cmd);
			}
		}
		clean_paths(paths);
	}
	return (ft_strdup(cmd));
}

t_cmd	*fill_lst_cmd(char *built_cmd, char *cmd, int is_empty)
{
	t_cmd		*lst_cmd;

	lst_cmd = NULL;
	if (is_empty)
		lst_cmd = fill_empty_cmd(cmd);
	else
		lst_cmd = fill_non_empty_cmd(built_cmd, cmd);
	return (lst_cmd);
}

t_cmd	*cmd_new(char *cmd)
{
	char	*built_cmd;
	char	*abs_cmd;
	t_cmd	*lst_cmd;

	lst_cmd = NULL;
	if (is_empty(cmd))
		return (fill_lst_cmd(cmd, cmd, 1));
	built_cmd = add_path(cmd);
	if (!built_cmd)
		return (NULL);
	abs_cmd = ft_substr(built_cmd, 0, cmd_len(built_cmd));
	if ((access(abs_cmd, F_OK) != 0 && access(abs_cmd, X_OK) != 0)
		|| is_empty(cmd))
	{
		lst_cmd = fill_lst_cmd(built_cmd, cmd, 0);
		if (errno == ENOENT)
			ft_printf("Command not found: %s\n", abs_cmd);
		else
			ft_printf("%s: %s\n", strerror(errno), abs_cmd);
	}
	else
		lst_cmd = fill_lst_cmd(built_cmd, cmd, 0);
	free(abs_cmd);
	free(built_cmd);
	return (lst_cmd);
}

int	compose_cmd(char *cmd, t_cmd **lst_cmd)
{
	t_cmd	*lst_cmd_new;

	if (is_empty(cmd))
		ft_printf("Command not found: %s\n", cmd);
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
