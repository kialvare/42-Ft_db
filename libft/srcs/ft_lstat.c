/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 15:02:11 by kcheung           #+#    #+#             */
/*   Updated: 2016/11/19 15:02:12 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Returns node at Nth position. Returns Null if N not within sze of list.
*/

#include "libft.h"

t_list	*ft_lstat(t_list *begin_list, unsigned int nbr)
{
	t_list			*temp;
	unsigned int	i;
	unsigned int	size;

	i = 0;
	temp = begin_list;
	size = ft_lstsize(begin_list);
	if (nbr < 1 || nbr > size)
		return (0);
	else if (nbr == 1)
		return (begin_list);
	else
	{
		while (i < nbr - 1)
		{
			temp = temp->next;
			i++;
		}
		return (temp);
	}
}
