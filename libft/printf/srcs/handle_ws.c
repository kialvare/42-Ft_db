/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ws.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 11:14:23 by kcheung           #+#    #+#             */
/*   Updated: 2017/04/23 18:24:59 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

unsigned int	calc_wstrlen(wchar_t *str, int precision, size_t i)
{
	if (*str == '\0' || precision == 0)
		return (i);
	else if (*str <= 0x7F)
		return (calc_wstrlen(str + 1, precision - 1, i + 1));
	else if (*str <= 0x7FF && precision >= 2)
		return (calc_wstrlen(str + 1, precision - 2, i + 2));
	else if (*str <= 0xFFFF && precision >= 3)
		return (calc_wstrlen(str + 1, precision - 3, i + 3));
	else if (*str <= 0x10FFFF && precision >= 4)
		return (calc_wstrlen(str + 1, precision - 4, i + 4));
	else
		return (i);
}

ssize_t			pf_handle_ws(char **fmt, va_list args, t_fmt *fl)
{
	wchar_t		*str;
	size_t		strlen;
	ssize_t		ret;

	ret = 0;
	str = va_arg(args, wchar_t *);
	if (!str)
		str = L"(null)";
	strlen = fl->precision ? calc_wstrlen(str, fl->precision_val, 0) :
		ft_wcslen(str);
	if (!fl->left_justify)
	{
		if (fl->width && !fl->pad_zeroes)
			ret += pf_pad(strlen, fl->width_val, ' ');
		else if (fl->width && fl->pad_zeroes)
			ret += pf_pad(strlen, fl->width_val, '0');
	}
	ft_putnwstr(str, strlen);
	ret += strlen;
	if (fl->left_justify)
		ret += pf_pad(strlen, fl->width_val, ' ');
	return (ret);
	(void)fmt;
	(void)fl;
}
