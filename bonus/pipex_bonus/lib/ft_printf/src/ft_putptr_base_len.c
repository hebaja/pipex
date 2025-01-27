/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_base_len.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:22:07 by hebatist          #+#    #+#             */
/*   Updated: 2024/10/28 17:22:10 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	ft_putptr_base_len(unsigned long nbr, char *base, int *len)
{
	unsigned long	size;

	size = ft_strlen(base);
	if (nbr < size)
	{
		*(len) += ft_putchar_len(base[nbr]);
		return ;
	}
	ft_putnbr_base_len(nbr / size, base, len);
	ft_putnbr_base_len(nbr % size, base, len);
}
