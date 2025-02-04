/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:40:31 by hebatist          #+#    #+#             */
/*   Updated: 2024/09/29 15:40:33 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_ptr;
	unsigned char	*src_ptr;

	dest_ptr = (unsigned char *)dest;
	src_ptr = (unsigned char *)src;
	if (dest <= src)
		ft_memcpy(dest, src, n);
	else if (dest > src)
	{
		dest_ptr += n - 1;
		src_ptr += n - 1;
		while (n--)
			*dest_ptr-- = *src_ptr--;
	}
	return (dest);
}
