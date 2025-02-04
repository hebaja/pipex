/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:44:34 by hebatist          #+#    #+#             */
/*   Updated: 2024/09/29 16:07:40 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	int		start;
	int		end;

	start = 0;
	end = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[start]) && start <= end)
		start++;
	while (ft_strchr(set, s1[end]) && end >= 0)
		end--;
	if (start > end)
	{
		ptr = (char *)malloc(1);
		if (ptr == NULL)
			return (NULL);
		ptr[0] = '\0';
		return (ptr);
	}
	ptr = (char *)malloc(end - start + 2);
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, &s1[start], end - start + 2);
	return (ptr);
}
