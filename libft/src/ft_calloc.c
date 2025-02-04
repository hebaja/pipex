/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:43:41 by hebatist          #+#    #+#             */
/*   Updated: 2024/10/11 00:08:16 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;

	if (nmemb == 0 || size == 0)
	{
		ptr = (unsigned char *)malloc(1);
		if (ptr == NULL)
			return (NULL);
	}
	else if (nmemb > (2147483647 / size))
		return (NULL);
	else
	{
		ptr = (unsigned char *)malloc(nmemb * size);
		if (ptr == NULL)
			return (NULL);
		ft_bzero(ptr, nmemb * size);
	}
	return (ptr);
}
