/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 11:08:49 by kcheung           #+#    #+#             */
/*   Updated: 2017/02/26 17:35:47 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

ssize_t	pf_handle_x(char **fmt, va_list args, t_fmt *fl)
{
	uintmax_t	nbr;
	char		*pfx;

	nbr = pf_get_unsigned(args, fl);
	if (fl->force_alt && nbr)
		fl->width_val -= 2;
	if (**fmt == 'X')
	{
		pfx = NULL;
		if (fl->force_alt && nbr)
			pfx = "0X";
		return (pf_printnbr(pfx, fl, nbr, "0123456789ABCDEF"));
	}
	else
	{
		pfx = NULL;
		if (fl->force_alt && nbr)
			pfx = "0x";
		return (pf_printnbr(pfx, fl, nbr, "0123456789abcdef"));
	}
	(void)fmt;
	(void)fl;
	(void)args;
}
