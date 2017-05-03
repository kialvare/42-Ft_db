/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 22:49:34 by kcheung           #+#    #+#             */
/*   Updated: 2016/11/16 22:49:35 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	char *temp;

	temp = dst;
	while (len)
	{
		if (*src == '\0')
		{
			ft_bzero(temp, len);
			return (dst);
		}
		*temp = *src;
		temp++;
		src++;
		len--;
	}
	return (dst);
}
