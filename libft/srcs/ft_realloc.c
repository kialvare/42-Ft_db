/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 16:47:45 by kcheung           #+#    #+#             */
/*   Updated: 2017/04/23 17:37:17 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	char *temp;

	if (!size && ptr)
	{
		if (!(temp = (char *)malloc(1)))
			return (0);
		ft_memdel(&ptr);
		return (temp);
	}
	if (!(temp = ft_strnew(size)))
		return (0);
	if (ptr)
	{
		ft_memcpy(temp, ptr, size);
		ft_memdel(&ptr);
	}
	return (temp);
}
