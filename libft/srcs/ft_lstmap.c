/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 16:53:33 by kcheung           #+#    #+#             */
/*   Updated: 2016/11/16 16:53:35 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *newhead;
	t_list *cpy;
	t_list *tmp;

	if (!lst || !f)
		return (NULL);
	cpy = f(lst);
	if ((newhead = ft_lstnew(cpy->content, cpy->content_size)))
	{
		tmp = newhead;
		lst = lst->next;
		while (lst)
		{
			cpy = f(lst);
			tmp->next = ft_lstnew(cpy->content, cpy->content_size);
			lst = lst->next;
			tmp = tmp->next;
		}
	}
	return (newhead);
}
