/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_o.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 10:59:50 by kcheung           #+#    #+#             */
/*   Updated: 2017/02/23 12:33:07 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

ssize_t	pf_handle_o(char **fmt, va_list args, t_fmt *fl)
{
	uintmax_t	nbr;
	char		*pfx;

	pfx = "0";
	nbr = pf_get_unsigned(args, fl);
	if (fl->force_alt)
		fl->width_val -= 1;
	if ((fl->force_alt && fl->precision && fl->precision_val) ||
			(fl->force_alt && !nbr && !fl->precision))
		pfx = NULL;
	return (pf_printnbr(pfx, fl, nbr, "01234567"));
	(void)fmt;
	(void)fl;
	(void)args;
}

ssize_t	pf_handle_o2(char **fmt, va_list args, t_fmt *fl)
{
	fl->length = l;
	return (pf_get_handler(ft_tolower(**fmt))(fmt, args, fl));
	(void)fmt;
	(void)fl;
	(void)args;
}
