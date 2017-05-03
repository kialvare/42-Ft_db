/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseflags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 22:50:34 by kcheung           #+#    #+#             */
/*   Updated: 2017/04/13 16:29:30 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*pf_parse_fl(char *fmt, t_fmt *fl)
{
	if ((ft_isalpha(*fmt) && !is_instr(*fmt, "hljz")) || *fmt == '%' || !*fmt)
		return (fmt);
	if (*fmt == '-' || *fmt == '0' || *fmt == '+' || *fmt == ' ' || *fmt == '#')
	{
		if (*fmt == '-')
			fl->left_justify = 1;
		else if (*fmt == '0')
			fl->pad_zeroes = 1;
		else if (*fmt == '+')
			fl->force_sign = 1;
		else if (*fmt == ' ')
			fl->force_space = 1;
		else if (*fmt == '#')
			fl->force_alt = 1;
		(fmt)++;
	}
	else if (ft_isdigit(*fmt))
	{
		while (ft_isdigit(*fmt))
			fmt++;
	}
	else
		fmt++;
	return (pf_parse_fl(fmt, fl));
}

size_t	pf_wild(t_fmt *fl, va_list args, int wp)
{
	int	val;

	val = va_arg(args, int);
	if (val < 0)
	{
		if (wp == 0)
		{
			fl->left_justify = 1;
			return (-val);
		}
		else if (wp == 1)
		{
			fl->precision = 0;
			fl->pad_zeroes = 1;
			return (0);
		}
	}
	return (val);
}

char	*pf_parse_width(char *fmt, t_fmt *fl, va_list args)
{
	if ((ft_isalpha(*fmt) && !is_instr(*fmt, "hljz")) || *fmt == '%' || !*fmt)
		return (fmt);
	else if ((*fmt != '0' && ft_isdigit(*fmt)) || *fmt == '*')
	{
		fl->width = 1;
		fl->width_val = 0;
		if (*fmt == '*')
		{
			fl->width_val = pf_wild(fl, args, 0);
			fmt += 1;
		}
		else
		{
			while (ft_isdigit(*fmt))
			{
				fl->width_val = fl->width_val * 10 + (*fmt - '0');
				(fmt)++;
			}
		}
	}
	else if (*fmt == '.')
		skip_numb(&fmt);
	else if (*fmt == '0' || *fmt)
		fmt++;
	return (pf_parse_width(fmt, fl, args));
}

char	*pf_parse_precision(char *fmt, va_list args, t_fmt *fl)
{
	if ((ft_isalpha(*fmt) && !is_instr(*fmt, "hljz")) || *fmt == '%'
			|| !*fmt)
		return (fmt);
	if (*fmt == '.')
	{
		fl->precision = 1;
		(fmt)++;
		if (*fmt == '*')
		{
			fl->precision_val = pf_wild(fl, args, 1);
			fmt += 1;
		}
		while (ft_isdigit(*fmt))
		{
			fl->precision_val = fl->precision_val * 10 + (*fmt - '0');
			(fmt)++;
		}
	}
	else
		fmt++;
	return (pf_parse_precision(fmt, args, fl));
}

char	*pf_parse_length(char *fmt, t_fmt *fl)
{
	if ((is_end(*fmt) && !is_instr(*fmt, "hljz")) || *fmt == '%' || !*fmt)
		return (fmt);
	if ((*fmt == 'h' && *(fmt + 1) == 'h') ||
			(*fmt == 'l' && *(fmt + 1) == 'l'))
	{
		fl->length = (*fmt == 'h') ? hh : ll;
		fmt += 2;
	}
	else if (is_instr(*fmt, "hljz") && *fmt)
	{
		if (*fmt == 'h')
			fl->length = h;
		else if (*fmt == 'l')
			fl->length = l;
		else if (*fmt == 'j')
			fl->length = j;
		else if (*fmt == 'z')
			fl->length = z;
		else
			fl->length = none;
		fmt += 1;
	}
	else
		fmt++;
	return (pf_parse_length(fmt, fl));
}
