/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:40:07 by hebatist          #+#    #+#             */
/*   Updated: 2024/10/05 17:32:39 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*src_ptr;
	unsigned char		*dest_ptr;

	dest_ptr = dest;
	src_ptr = src;
	while (n--)
		*dest_ptr++ = (unsigned char)*src_ptr++;
	return (dest);
}
