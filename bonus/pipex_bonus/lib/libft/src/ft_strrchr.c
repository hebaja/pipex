/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:42:32 by hebatist          #+#    #+#             */
/*   Updated: 2024/10/04 21:58:23 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				len;
	unsigned char	ch;

	len = ft_strlen(s);
	ch = c;
	while (len > -1)
	{
		if (s[len] == ch)
			return ((char *)(&s[len]));
		len--;
	}
	return (0);
}
