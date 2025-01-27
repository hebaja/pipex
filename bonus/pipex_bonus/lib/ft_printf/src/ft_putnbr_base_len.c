/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_len.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:21:50 by hebatist          #+#    #+#             */
/*   Updated: 2024/10/28 17:21:54 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	ft_putnbr_base_len(long nbr, char *base, int *len)
{
	long	size;

	size = ft_strlen(base);
	if (nbr < 0)
	{
		*(len) += ft_putchar_len(45);
		nbr *= -1;
	}
	if (nbr < size)
	{
		*(len) += ft_putchar_len(base[nbr]);
		return ;
	}
	ft_putnbr_base_len(nbr / size, base, len);
	ft_putnbr_base_len(nbr % size, base, len);
}
