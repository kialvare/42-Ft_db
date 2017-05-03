/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 22:53:13 by kcheung           #+#    #+#             */
/*   Updated: 2017/02/26 14:40:07 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*assign_char(long n, char *str)
{
	int c;

	if (n == 0)
		return (NULL);
	c = n % 10 + '0';
	assign_char(n / 10, str);
	while (n /= 10)
		str++;
	*str = c;
	return (str);
}

static	int		digits(long i)
{
	int r;

	r = 1;
	while (i != 0)
	{
		i /= 10;
		r++;
	}
	if (i < 0)
		r++;
	return (r);
}

char			*ft_itoa(int n)
{
	char *str;
	char *temp;
	long cpy;

	cpy = (long)n;
	if ((str = ft_strnew(digits(cpy))) == NULL)
		return (NULL);
	temp = str;
	if (cpy == 0)
	{
		*temp = '0';
		return (str);
	}
	else if (cpy < 0)
	{
		cpy = cpy * -1;
		*temp++ = '-';
	}
	temp = assign_char(cpy, temp);
	*++temp = '\0';
	return (str);
}
