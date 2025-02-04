/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:35:06 by hebatist          #+#    #+#             */
/*   Updated: 2024/10/28 17:25:05 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		len;

	len = 0;
	if (str == NULL)
		return (-1);
	va_start(args, str);
	while (*str)
	{
		if (*(str) == '%')
		{
			len += print_type(str, args);
			str += 2;
		}
		else if (*str)
		{
			len += ft_putchar_len(*str);
			str += 1;
		}
	}
	va_end(args);
	return (len);
}
