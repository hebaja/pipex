/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 23:58:25 by hebatist          #+#    #+#             */
/*   Updated: 2024/10/10 14:56:54 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	iter(t_list *lst, void (*f)(void *))
{
	(*f)(lst->content);
	if (lst->next)
		iter(lst->next, f);
}

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (lst && f)
		iter(lst, f);
}
