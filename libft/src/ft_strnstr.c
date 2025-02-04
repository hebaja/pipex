/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:43:21 by hebatist          #+#    #+#             */
/*   Updated: 2024/09/29 15:58:47 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int	a;
	int	b;
	int	len_tmp;

	a = 0;
	if (little[0] == '\0')
		return ((char *)big);
	if (big != NULL)
	{
		while (big[a] && len > 0)
		{
			b = 0;
			len_tmp = len;
			while (big[a + b] == little[b] && big[a + b] && len_tmp)
			{
				if (little[b + 1] == '\0')
					return ((char *)(&big[a]));
				b++;
				len_tmp--;
			}
			a++;
			len--;
		}
	}
	return (0);
}
