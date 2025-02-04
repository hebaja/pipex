/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 23:58:40 by hebatist          #+#    #+#             */
/*   Updated: 2024/10/10 14:57:27 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*n_lst;
	t_list	*current_lst;
	t_list	*first_ptr;

	first_ptr = NULL;
	if (lst && f && del)
	{
		n_lst = ft_lstnew((*f)(lst->content));
		if (!n_lst)
			return (NULL);
		first_ptr = n_lst;
		current_lst = lst;
		while (current_lst->next)
		{
			n_lst->next = ft_lstnew((*f)(current_lst->next->content));
			if (!n_lst->next)
			{
				ft_lstclear(&first_ptr, del);
				return (NULL);
			}
			n_lst = n_lst->next;
			current_lst = current_lst->next;
		}
	}
	return (first_ptr);
}
