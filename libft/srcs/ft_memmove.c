/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 16:15:15 by kcheung           #+#    #+#             */
/*   Updated: 2016/11/02 16:15:16 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*tmp_dst;
	char	*tmp_src;
	size_t	i;

	tmp_dst = (char *)dst;
	tmp_src = (char *)src;
	i = 0;
	while (i < len)
	{
		if (dst == src + i)
		{
			while (len)
			{
				tmp_dst[len - 1] = tmp_src[len - 1];
				len--;
			}
			return (tmp_dst);
		}
		i++;
	}
	return (ft_memcpy(tmp_dst, tmp_src, len));
}
