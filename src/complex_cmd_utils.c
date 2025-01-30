/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_cmd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 23:39:33 by hebatist          #+#    #+#             */
/*   Updated: 2025/01/29 23:39:43 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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
	str_new = (char *)malloc(sizeof(char) * (len + 1));
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
	}
	str_new[j] = '\0';
	return (str_new);
}

int	options_quant(char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == '-' && *(str - 1) == ' ' && ft_isalnum(*(str + 1)))
			count++;
		str++;
	}
	return (count);
}
