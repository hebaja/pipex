/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 19:29:17 by hebatist          #+#    #+#             */
/*   Updated: 2024/10/05 15:58:26 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	get_height(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		if (*s && *s != c)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

int	get_word_len(const char *s, char c)
{
	int	len;

	len = 0;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

int	populate_matrix(char **strs, char const *s, char c, int *i)
{
	char	*ptr;

	ptr = ft_substr(s, 0, get_word_len(s, c));
	if (ptr == NULL)
	{
		while (*i <= 0)
		{
			free(strs[*i]);
			(*i)--;
		}
		free(strs);
		return (0);
	}
	(*i)++;
	strs[*i] = ptr;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		res;
	int		i;

	i = -1;
	strs = (char **)malloc(sizeof(char *) * (get_height(s, c) + 1));
	if (strs == NULL)
		return (NULL);
	i = -1;
	while (*s)
	{
		if (*s == c)
			s++;
		if (*s && *s != c)
		{
			res = populate_matrix(strs, s, c, &i);
			if (!res)
				return (NULL);
		}
		while (*s && *s != c)
			s++;
	}
	strs[++i] = NULL;
	return (strs);
}
