/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 01:39:54 by hebatist          #+#    #+#             */
/*   Updated: 2025/01/24 01:39:56 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

char    **fetch_path(char **envp)
{
	int     i;
	char    *target = "PATH";
	char    *path;
	char    **split_path;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], target, ft_strlen(target)) == 0 && envp[i][ft_strlen(target)] == '=')
			path = envp[i];
		i++;
	}
	split_path = ft_split(ft_strchr(path, '/'), ':');
	return (split_path);
}

void	clean_path(char **paths)
{
	int	i;

	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
}
