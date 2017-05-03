/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 21:42:44 by kcheung           #+#    #+#             */
/*   Updated: 2017/04/13 16:30:52 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*pf_check_fl(char *fmt, va_list args, t_fmt *flag)
{
	if ((pf_parse_fl(fmt, flag)) == NULL)
		return (NULL);
	if ((pf_parse_width(fmt, flag, args)) == NULL)
		return (NULL);
	if ((pf_parse_precision(fmt, args, flag)) == NULL)
		return (NULL);
	if ((fmt = pf_parse_length(fmt, flag)) == NULL)
		return (NULL);
	return (fmt);
}

void	pf_print(char **fmt, va_list args, ssize_t *ret)
{
	char		*ptr;
	char		*start;
	t_handle	handler;
	t_fmt		fl;

	ptr = *fmt;
	start = ptr;
	while ((ft_strchr(ptr, '%')) != NULL)
	{
		ft_bzero(&fl, sizeof(fl));
		ptr = ft_strchr(ptr, '%');
		ft_putnstr(start, ptr - start);
		*ret += ptr - start;
		ptr++;
		if (!*ptr || !*(ptr = pf_check_fl(ptr, args, &fl)))
			return ;
		if (!(handler = pf_get_handler(*ptr)))
			handler = &pf_handle_none;
		*ret += handler(&ptr, args, &fl);
		start = ptr + 1;
		ptr = start;
	}
	*ret += ft_putstr(ptr);
}

ssize_t	ft_printf(char *fmt, ...)
{
	va_list	args;
	ssize_t	ret;

	ret = 0;
	va_start(args, fmt);
	pf_print(&fmt, args, &ret);
	va_end(args);
	return (ret);
}
