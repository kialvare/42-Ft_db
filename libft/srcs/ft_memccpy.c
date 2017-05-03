/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 19:15:17 by kcheung           #+#    #+#             */
/*   Updated: 2016/11/02 19:15:18 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char *cdst;
	char *csrc;

	cdst = (char *)dst;
	csrc = (char *)src;
	while (n > 0)
	{
		*cdst = *csrc;
		if (*csrc == c)
			return (cdst + 1);
		else
		{
			cdst++;
			csrc++;
			n--;
		}
	}
	return (NULL);
}
