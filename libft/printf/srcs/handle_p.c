/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 22:39:36 by kcheung           #+#    #+#             */
/*   Updated: 2017/02/23 12:34:48 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

ssize_t	pf_handle_p(char **fmt, va_list args, t_fmt *fl)
{
	uintmax_t	nbr;

	(void)fmt;
	fl->length = z;
	if (fl->precision)
		fl->pad_zeroes = 0;
	nbr = pf_get_unsigned(args, fl);
	return (pf_force_pfx("0x", fl, nbr, "0123456789abcdef"));
}
