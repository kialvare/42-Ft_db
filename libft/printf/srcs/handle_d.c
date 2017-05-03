/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 12:41:28 by kcheung           #+#    #+#             */
/*   Updated: 2017/02/23 12:35:06 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

intmax_t	pf_get_signed(va_list args, t_fmt *fl)
{
	intmax_t	nbr;

	nbr = va_arg(args, intmax_t);
	if (fl->length == hh)
		nbr = (char)nbr;
	else if (fl->length == h)
		nbr = (short int)nbr;
	else if (fl->length == l)
		nbr = (long int)nbr;
	else if (fl->length == ll)
		nbr = (long long int)nbr;
	else if (fl->length == j)
		nbr = (intmax_t)nbr;
	else if (fl->length == z)
		nbr = (size_t)nbr;
	else
		nbr = (int)nbr;
	return (nbr);
}

ssize_t		pf_handle_d(char **fmt, va_list args, t_fmt *fl)
{
	intmax_t	nbr;
	char		*prefix;

	nbr = pf_get_signed(args, fl);
	prefix = NULL;
	if (nbr < 0 || fl->force_sign || fl->force_space)
	{
		if (nbr < 0)
		{
			nbr = -nbr;
			prefix = "-";
		}
		else if (fl->force_sign)
			prefix = "+";
		else if (fl->force_space)
			prefix = " ";
		else
			prefix = "";
		return (pf_force_pfx(prefix, fl, nbr, "0123456789"));
	}
	else
		return (pf_printnbr(NULL, fl, nbr, "0123456789"));
	(void)fmt;
}

ssize_t		pf_handle_d2(char **fmt, va_list args, t_fmt *fl)
{
	fl->length = l;
	return (pf_get_handler(ft_tolower(**fmt))(fmt, args, fl));
	(void)fmt;
}
