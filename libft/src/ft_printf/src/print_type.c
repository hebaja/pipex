/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:22:46 by hebatist          #+#    #+#             */
/*   Updated: 2024/10/28 17:22:50 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	print_string(va_list args)
{
	char	*str;
	int		len;

	str = va_arg(args, char *);
	len = 0;
	if (str == NULL)
		len += ft_putstr_len("(null)");
	else
		len += ft_putstr_len(str);
	return (len);
}

int	print_number(char c, va_list args)
{
	int		len;
	char	*base;

	len = 0;
	base = "0123456789";
	if (c == 'd' || c == 'i')
		ft_putnbr_base_len(va_arg(args, int), base, &len);
	if (c == 'u')
		ft_putnbr_base_len(
			(unsigned int)va_arg(args, unsigned int), base, &len);
	return (len);
}

int	print_hex(char c, va_list args)
{
	void	*ptr;
	int		len;

	len = 0;
	if (c == 'x')
		ft_putnbr_base_len(
			(unsigned int)va_arg(args, unsigned int), "0123456789abcdef", &len);
	if (c == 'X')
		ft_putnbr_base_len(
			(unsigned int)va_arg(args, unsigned int), "0123456789ABCDEF", &len);
	if (c == 'p')
	{
		ptr = va_arg(args, void *);
		if (ptr == NULL)
			len += ft_putstr_len("(nil)");
		else
		{
			len += ft_putstr_len("0x");
			ft_putptr_base_len((unsigned long)ptr, "0123456789abcdef", &len);
		}
	}
	return (len);
}

int	print_type(const char *str, va_list args)
{
	int	len;

	len = 0;
	if (*(str + 1) == '%')
		len += ft_putchar_len('%');
	if (*(str + 1) == 'c')
		len += ft_putchar_len(va_arg(args, int));
	if (*(str + 1) == 's')
		len += print_string(args);
	if (*(str + 1) == 'd' || *(str + 1) == 'i' || *(str + 1) == 'u')
		len += print_number(*(str + 1), args);
	if (*(str + 1) == 'x' || *(str + 1) == 'X' || *(str + 1) == 'p')
		len += print_hex(*(str + 1), args);
	return (len);
}
