/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 16:47:58 by kcheung           #+#    #+#             */
/*   Updated: 2016/11/02 16:47:59 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	c2;

	c2 = (unsigned char)c;
	ptr = (unsigned char *)s;
	while (n)
	{
		if (*ptr == c2)
			return (ptr);
		ptr++;
		n--;
	}
	return (NULL);
}
