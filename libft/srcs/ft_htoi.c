/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_htoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 14:36:43 by kcheung           #+#    #+#             */
/*   Updated: 2017/02/26 14:36:58 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_raw(char c)
{
	if (ft_isalpha(c))
		return (ft_toupper(c) - 'A' + 10);
	return (c - '0');
}

int	ft_htoi(const char *hex)
{
	int	i;
	int	len;
	int	power;
	int	dec;

	dec = 0;
	len = ft_strlen(hex) - 1;
	i = len;
	power = 1;
	while (i >= 0)
	{
		dec += get_raw(hex[i]) * power;
		power *= 16;
		i--;
	}
	return (dec);
}
