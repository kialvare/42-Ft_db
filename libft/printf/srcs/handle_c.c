/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_c.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 11:09:41 by kcheung           #+#    #+#             */
/*   Updated: 2017/02/27 15:04:57 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

ssize_t	pf_handle_c(char **fmt, va_list args, t_fmt *fl)
{
	char			c;
	unsigned int	charlen;
	ssize_t			ret;

	ret = 0;
	if (fl->length == l)
		return (pf_handle_wc(fmt, args, fl));
	else
	{
		c = pf_get_unsigned(args, fl);
		charlen = 1;
		if (!fl->left_justify)
		{
			if (fl->width && !fl->pad_zeroes)
				ret += pf_pad(charlen, fl->width_val, ' ');
			else if (fl->width && fl->pad_zeroes)
				ret += pf_pad(charlen, fl->width_val, '0');
		}
		ft_putchar(c);
		ret += charlen;
		if (fl->left_justify)
			ret += pf_pad(charlen, fl->width_val, ' ');
		return (ret);
	}
	(void)fmt;
}
