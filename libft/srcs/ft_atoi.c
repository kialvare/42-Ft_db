/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 15:07:25 by kcheung           #+#    #+#             */
/*   Updated: 2017/04/07 10:42:45 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				is_valid_int(const char *s)
{
	long long	temp;
	int			negative;

	temp = 0;
	negative = 0;
	if (*s != '\0' && (*s == '-' || *s == '+'))
		negative = *s++ == '-';
	while (*s != '\0')
	{
		if (!ft_isdigit((unsigned char)*s))
			return (0);
		temp = 10 * temp + (*s - '0');
		if ((!negative && temp > INT_MAX) || (negative && -temp < INT_MIN))
			return (0);
		++s;
	}
	return (1);
}

static char		*skip_white(char *str, int *sign)
{
	while (*str < '0' || *str > '9')
	{
		if (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v' ||
			*str == '\f' || *str == '\r')
			str++;
		else if (*str == '+')
			return (str + 1);
		else if (*str == '-')
		{
			*sign = -1;
			return (str + 1);
		}
		else if (*str == '\0')
			return (str);
		else
			return (str);
	}
	return (str);
}

int				ft_atoi(const char *str)
{
	int		val;
	int		sign;
	char	*temp;

	sign = 1;
	val = 0;
	if (!is_valid_int(str))
		return (0);
	temp = skip_white((char*)str, &sign);
	if ((*temp <= '0' && *temp >= '9') || *temp == '\0')
		return (0);
	else
	{
		while (*temp >= '0' && *temp <= '9')
		{
			val = val * 10 + (*temp - '0') * sign;
			temp++;
		}
		return (val);
	}
}
