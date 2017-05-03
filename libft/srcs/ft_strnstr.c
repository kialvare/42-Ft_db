/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 13:49:49 by kcheung           #+#    #+#             */
/*   Updated: 2016/11/06 13:49:50 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	isn_little(char *big, char *little)
{
	while (*little)
	{
		if (*big == *little)
		{
			big++;
			little++;
		}
		else
			return (0);
	}
	return (1);
}

char		*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*temp;
	char	*ptr;
	int		count;

	temp = (char*)little;
	count = 0;
	if (!*little)
		return ((char*)big);
	while (*big)
	{
		if (count + ft_strlen(temp) > len)
			return (0);
		else if (*big == *temp)
		{
			ptr = (char*)big;
			if (isn_little((char*)big, temp))
				return (ptr);
		}
		count++;
		big++;
	}
	return (0);
}
