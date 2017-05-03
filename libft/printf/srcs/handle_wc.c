/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 11:13:48 by kcheung           #+#    #+#             */
/*   Updated: 2017/02/23 12:34:31 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

ssize_t	ft_wchlen(const wchar_t c)
{
	int len;

	len = 0;
	if (c <= 0x7F)
		len = 1;
	else if (c <= 0x7FF)
		len = 2;
	else if (c <= 0xFFFF)
		len = 3;
	else if (c <= 0x10FFFF)
		len = 4;
	else
		len = 0;
	return (len);
}

ssize_t	pf_handle_wc(char **fmt, va_list args, t_fmt *fl)
{
	wchar_t		c;
	unsigned	charlen;
	ssize_t		ret;

	ret = 0;
	c = va_arg(args, wchar_t);
	charlen = ft_wchlen(c);
	if (!fl->left_justify)
	{
		if (fl->width && !fl->pad_zeroes)
			ret += pf_pad(charlen, fl->width_val, ' ');
		else if (fl->width && fl->pad_zeroes)
			ret += pf_pad(charlen, fl->width_val, '0');
	}
	ft_putwchar(c);
	ret += charlen;
	if (fl->left_justify)
		ret += pf_pad(charlen, fl->width_val, ' ');
	return (ret);
	(void)fmt;
}
