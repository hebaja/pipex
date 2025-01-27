/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 23:57:17 by hebatist          #+#    #+#             */
/*   Updated: 2024/10/10 14:57:10 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current_lst;

	current_lst = lst;
	while (current_lst)
	{
		if (current_lst->next == NULL)
			break ;
		current_lst = current_lst->next;
	}
	return (current_lst);
}
