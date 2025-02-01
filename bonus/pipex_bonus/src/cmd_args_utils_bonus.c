/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_cmd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 23:39:33 by hebatist          #+#    #+#             */
/*   Updated: 2025/01/30 20:48:06 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	contains_quote(char *str)
{
	while (*str)
	{
		if (*str == 39)
			return (1);
		str++;
	}
	return (0);
}

size_t	quote_quant(const char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == 39)
			count++;
		str++;
	}
	return (count);
}

char	*remove_quotes(const char *str)
{
	char		*str_new;
	int			len;
	int			i;
	int			j;

	len = ft_strlen(str) - quote_quant(str);
	str_new = ft_calloc(sizeof(char), len + 1);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == 39)
			i++;
		else
		{
			str_new[j] = str[i];
			i++;
			j++;
		}
		if (str[i] == 39)
			break ;
	}
	str_new[j] = '\0';
	return (str_new);
}

char	*catch_option(char *str)
{
	char		*str_new;
	int			i;
	int			len;

	i = 0;
	len = 0;
	while (str[len] && str[len] != ' ')
		len++;
	str_new = ft_calloc(sizeof(char), len + 1);
	while (str[i] && str[i] != ' ')
	{
		str_new[i] = str[i];
		i++;
	}
	str_new[i] = '\0';
	return (str_new);
}
