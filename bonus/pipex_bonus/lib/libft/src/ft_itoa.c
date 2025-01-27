/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 21:04:04 by hebatist          #+#    #+#             */
/*   Updated: 2024/10/04 23:36:19 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	get_n_len(int n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		if (n == -2147483648)
		{
			n = 147483648;
			len++;
		}
		else
			n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*alloc_str(int n, int *len)
{
	char	*str;

	if (n < 0)
		(*len)++;
	str = (char *)malloc(sizeof(char) * (*len + 1));
	return (str);
}

void	case_n_negative(char *str, int *n)
{
	str[0] = '-';
	if (*n == -2147483648)
	{
		str[1] = '2';
		*n = 147483648;
	}
	else
		*(n) *= -1;
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;

	len = get_n_len(n);
	if (n == 0)
	{
		str = (char *)malloc(sizeof(char) * 2);
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	str = alloc_str(n, &len);
	if (str == NULL)
		return (NULL);
	if (n < 0)
		case_n_negative(str, &n);
	str[len] = '\0';
	while (n > 0)
	{
		str[--len] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
