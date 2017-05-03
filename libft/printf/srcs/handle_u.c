/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 11:06:46 by kcheung           #+#    #+#             */
/*   Updated: 2017/02/22 23:47:21 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

ssize_t	pf_handle_u(char **fmt, va_list args, t_fmt *fl)
{
	uintmax_t	nbr;

	nbr = pf_get_unsigned(args, fl);
	return (pf_printnbr(NULL, fl, nbr, "0123456789"));
	(void)fmt;
	(void)fl;
	(void)args;
}

ssize_t	pf_handle_u2(char **fmt, va_list args, t_fmt *fl)
{
	fl->length = l;
	return (pf_get_handler(ft_tolower(**fmt))(fmt, args, fl));
	(void)fmt;
	(void)fl;
	(void)args;
}
