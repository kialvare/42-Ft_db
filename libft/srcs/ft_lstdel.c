/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 15:26:14 by kcheung           #+#    #+#             */
/*   Updated: 2016/11/16 15:26:15 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*temp;
	t_list	*nxtlst;

	if (!alst || !del)
		return ;
	temp = *alst;
	while (temp)
	{
		nxtlst = temp->next;
		del(temp->content, temp->content_size);
		free(temp);
		temp = nxtlst;
	}
	*alst = NULL;
}
