/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 22:45:22 by kcheung           #+#    #+#             */
/*   Updated: 2017/04/13 16:29:00 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			is_instr(char c, char *str)
{
	while (*str)
	{
		if (c == *str)
			return (1);
		str++;
	}
	return (0);
}

int			is_end(char c)
{
	if ((c >= '<' && c <= '~') || is_instr(c, "()!$/&") == 1)
		return (1);
	return (0);
}

void		skip_numb(char **fmt)
{
	(*fmt)++;
	if (**fmt == '*')
		(*fmt)++;
	else
	{
		while (**fmt == '.' || ft_isdigit(**fmt))
			(*fmt)++;
	}
}

size_t		pf_getnbr_len(intmax_t nbr, char *base)
{
	size_t	count;

	count = 0;
	if (!nbr || !base)
		return (count += 1);
	while (nbr)
	{
		nbr /= ft_strlen(base);
		count++;
	}
	return (count);
}

uintmax_t	pf_get_unsigned(va_list args, t_fmt *fl)
{
	uintmax_t	nbr;

	nbr = va_arg(args, uintmax_t);
	if (fl->length == hh)
		nbr = (unsigned char)nbr;
	else if (fl->length == h)
		nbr = (unsigned short int)nbr;
	else if (fl->length == l)
		nbr = (unsigned long int)nbr;
	else if (fl->length == ll)
		nbr = (unsigned long long int)nbr;
	else if (fl->length == j)
		nbr = (uintmax_t)nbr;
	else if (fl->length == z)
		nbr = (size_t)nbr;
	else
		nbr = (unsigned int)nbr;
	return (nbr);
}
