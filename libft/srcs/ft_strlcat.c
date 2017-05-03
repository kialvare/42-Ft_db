/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 23:09:00 by kcheung           #+#    #+#             */
/*   Updated: 2016/11/02 23:09:01 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	n;
	unsigned int	dlen;
	unsigned int	slen;

	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	n = size - dlen - 1;
	if (dlen > size - 1 || !size)
		return (slen + size);
	else
	{
		while (*dst)
			dst++;
		while (n)
		{
			if (!*src)
				break ;
			*dst = *src;
			dst++;
			src++;
			n--;
		}
		*dst++ = '\0';
		return (dlen + slen);
	}
}
