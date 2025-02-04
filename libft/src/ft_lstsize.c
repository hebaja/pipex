/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 23:56:53 by hebatist          #+#    #+#             */
/*   Updated: 2024/10/10 14:57:40 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*current_lst;
	int		size;

	size = 0;
	if (lst == NULL)
		return (0);
	current_lst = lst;
	while (current_lst)
	{
		current_lst = current_lst->next;
		size++;
	}
	return (size);
}
