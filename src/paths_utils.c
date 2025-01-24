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

#include "../include/pipex.h"

char	**build_paths(void)
{
	char	**paths;

	paths = (char **)malloc(sizeof(char *) * 7);
	paths[0] = ft_strdup("/usr/bin/");
	paths[1] = ft_strdup("/usr/sbin/");
	paths[2] = ft_strdup("/bin/");
	paths[3] = ft_strdup("/sbin/");
	paths[4] = ft_strdup("/usr/local/bin/");
	paths[5] = ft_strdup("/usr/local/sbin/");
	paths[6] = NULL;
	return (paths);
}

void	clean_paths(char **paths)
{
	int	i;

	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
}
