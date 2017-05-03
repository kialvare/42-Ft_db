/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 18:40:57 by kcheung           #+#    #+#             */
/*   Updated: 2016/11/05 18:40:59 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static	int	is_little(char *big, char *little)
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

char		*ft_strstr(const char *big, const char *little)
{
	char *temp;
	char *ptr;

	temp = (char*)little;
	if (!*little)
		return ((char*)big);
	while (*big)
	{
		if (*big == *temp)
		{
			ptr = (char*)big;
			if (is_little((char*)big, temp))
				return (ptr);
		}
		big++;
	}
	return (0);
}
