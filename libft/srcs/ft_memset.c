/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 13:00:42 by kcheung           #+#    #+#             */
/*   Updated: 2016/11/02 13:00:45 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t len)
{
	unsigned char	*temp;
	unsigned int	i;
	unsigned char	uc;

	temp = (unsigned char *)str;
	i = 0;
	uc = c;
	while (i < len)
	{
		temp[i] = uc;
		i++;
	}
	return ((void*)str);
}
