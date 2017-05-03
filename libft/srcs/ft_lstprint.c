/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printlist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 14:39:52 by kcheung           #+#    #+#             */
/*   Updated: 2016/11/19 14:39:54 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Returns node at Nth position. Returns Null if N not within sze of list.
*/

#include "libft.h"

void	ft_lstprint(t_list *list)
{
	while (list)
	{
		ft_putstr(list->content);
		ft_putchar(' ');
		list = list->next;
	}
}
