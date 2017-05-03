/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_s.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 11:11:50 by kcheung           #+#    #+#             */
/*   Updated: 2017/02/23 13:27:01 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

size_t	pf_calcstrlen(char *str, t_fmt *fl)
{
	size_t	strlen;

	if (!str && fl->precision && fl->precision_val == 0)
		strlen = 0;
	else if (fl->precision)
		if (fl->precision_val < ft_strlen(str))
			strlen = fl->precision_val;
		else
			strlen = ft_strlen(str);
	else
		strlen = ft_strlen(str);
	return (strlen);
}

ssize_t	pf_handle_s(char **fmt, va_list args, t_fmt *fl)
{
	char	*str;
	int		strlen;
	ssize_t	ret;

	ret = 0;
	if (fl->length == l)
		return (pf_handle_ws(fmt, args, fl));
	else
	{
		if (!(str = va_arg(args, char*)))
			str = "(null)";
		strlen = pf_calcstrlen(str, fl);
		if (!fl->left_justify)
		{
			if (fl->width)
				ret += (fl->pad_zeroes) ? pf_pad(strlen, fl->width_val, '0') :
					pf_pad(strlen, fl->width_val, ' ');
		}
		ret += ft_putnstr(str, strlen);
		if (fl->left_justify)
			ret += pf_pad(strlen, fl->width_val, ' ');
		return (ret);
	}
	(void)fmt;
}
