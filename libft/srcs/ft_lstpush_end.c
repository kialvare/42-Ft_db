/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lpush_end.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 19:44:02 by kcheung           #+#    #+#             */
/*   Updated: 2017/03/01 22:49:14 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Pushes Node / List element to end of List.
*/

#include "libft.h"

void	ft_lstpush_end(t_list **begin, t_list *node)
{
	t_list *temp;

	if (*begin == NULL)
	{
		node->next = *begin;
		*begin = node;
	}
	else
	{
		temp = *begin;
		while (temp->next)
			temp = temp->next;
		temp->next = node;
	}
}
