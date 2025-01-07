/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 21:04:53 by hebatist          #+#    #+#             */
/*   Updated: 2024/10/24 20:59:51 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_putstr_len(char *str)
{
	int	len;

	len = 0;
	while (*str)
	{
		len += ft_putchar_len(*str);
		str++;
	}
	return (len);
}
