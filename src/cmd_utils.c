/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:57:06 by hebatist          #+#    #+#             */
/*   Updated: 2025/01/23 19:04:56 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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

size_t	cmd_len(char *cmd)
{
	size_t	count;

	count = 0;
	if (cmd)
	{
		while (*cmd == ' ' || *cmd == '\t')
			cmd++;
		while (*cmd && (*cmd != ' ' && *cmd != '\t'))
		{
			count++;
			cmd++;
		}
	}
	return (count);
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

char	**build_empty_args(char *empty_str)
{
	char	**empty_args;

	empty_args = (char **)malloc(sizeof(char *) * 2);
	if (!empty_args)
		return (NULL);
	empty_args[0] = ft_strdup(empty_str);
	empty_args[1] = NULL;
	return (empty_args);
}
