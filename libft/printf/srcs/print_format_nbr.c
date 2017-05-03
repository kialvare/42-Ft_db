/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_format_nbr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 22:58:16 by kcheung           #+#    #+#             */
/*   Updated: 2017/02/28 11:44:46 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	pf_putnbr_base(uintmax_t nbr, char *base)
{
	if (nbr % ft_strlen(base) != (unsigned long)nbr)
	{
		pf_putnbr_base(nbr / ft_strlen(base), base);
		pf_putnbr_base(nbr % ft_strlen(base), base);
	}
	else
		ft_putchar(base[nbr]);
}

ssize_t	pf_pad(unsigned int strlen, unsigned int width, int c)
{
	int		diff;
	ssize_t	ret;

	diff = 0;
	ret = 0;
	if (strlen < width)
		diff = width - strlen;
	while (diff)
	{
		ft_putchar(c);
		ret++;
		diff--;
	}
	return (ret);
}

size_t	pf_calclen(uintmax_t nbr, t_fmt *fl, char *base, char *pfx)
{
	size_t	strlen;
	size_t	nbrlen;

	nbrlen = pf_getnbr_len(nbr, base);
	if (nbr == 0 && fl->precision && fl->precision_val == 0)
		strlen = 0 + ft_strlen(pfx);
	else if (fl->precision)
		strlen = ft_maxint(fl->precision_val, nbrlen);
	else
		strlen = nbrlen;
	if (pfx)
		strlen += ft_strlen(pfx);
	return (strlen);
}

ssize_t	pf_force_pfx(char *prefix, t_fmt *fl, uintmax_t nbr, char *base)
{
	size_t			strlen;
	ssize_t			ret;

	ret = 0;
	strlen = pf_calclen(nbr, fl, base, prefix);
	if (fl->width && !fl->left_justify && !fl->pad_zeroes)
	{
		ret += pf_pad(strlen, fl->width_val, ' ');
		fl->width = 0;
	}
	fl->width_val -= ft_strlen(prefix);
	ret += ft_putstr(prefix);
	return (ret + pf_printnbr(NULL, fl, nbr, base));
}

ssize_t	pf_printnbr(char *pfx, t_fmt *fl, intmax_t nbr, char *base)
{
	size_t			nbrlen;
	size_t			strlen;
	ssize_t			ret;

	ret = 0;
	nbrlen = pf_getnbr_len(nbr, base);
	strlen = pf_calclen(nbr, fl, base, NULL);
	if (fl->precision)
		fl->pad_zeroes = 0;
	if (fl->width && !fl->left_justify && !fl->pad_zeroes)
		ret += pf_pad(strlen, fl->width_val, ' ');
	if (fl->force_alt && pfx != NULL)
		ret += ft_putstr(pfx);
	if (fl->precision)
		ret += pf_pad(nbrlen, strlen, '0');
	if (fl->pad_zeroes && !fl->left_justify)
		ret += pf_pad(strlen, fl->width_val, '0');
	if ((fl->precision && !fl->precision_val && !nbr))
		;
	else
		pf_putnbr_base(nbr, base);
	ret += (fl->precision && !fl->precision_val && !nbr) ? 0 : nbrlen;
	if (fl->left_justify)
		ret += pf_pad(strlen, fl->width_val, ' ');
	return (ret);
}
