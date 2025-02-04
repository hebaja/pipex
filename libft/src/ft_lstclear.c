/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 23:58:05 by hebatist          #+#    #+#             */
/*   Updated: 2024/10/10 14:56:23 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	clear(t_list *lst, void (*del)(void *))
{
	if (lst->next)
		clear(lst->next, del);
	ft_lstdelone(lst, del);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	if (*lst)
	{
		clear(*lst, del);
		*lst = NULL;
	}
}
