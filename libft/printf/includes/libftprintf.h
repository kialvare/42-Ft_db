/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 19:11:54 by kcheung           #+#    #+#             */
/*   Updated: 2017/02/26 14:02:11 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include "libft.h"
# include <limits.h>
# include <locale.h>
# include <wchar.h>
# include <inttypes.h>

typedef struct		s_fmt
{
	unsigned int	left_justify : 1;
	unsigned int	pad_zeroes : 1;
	unsigned int	force_sign : 1;
	unsigned int	force_space : 1;
	unsigned int	force_alt : 1;
	unsigned int	width : 1;
	unsigned int	precision : 1;
	unsigned int	width_val;
	unsigned int	precision_val;

	enum {
		none,
		hh,
		h,
		l,
		ll,
		j,
		z,
		t,
		L
	}				length;
}					t_fmt;

typedef ssize_t		(*t_handle)(char **, va_list, t_fmt*);
/*
**Handlers
*/
ssize_t				pf_handle_none(char **fmt, va_list args, t_fmt *fl);
ssize_t				pf_handle_d(char **fmt, va_list args, t_fmt *fl);
ssize_t				pf_handle_d2(char **fmt, va_list args, t_fmt *fl);
ssize_t				pf_handle_o(char **fmt, va_list args, t_fmt *fl);
ssize_t				pf_handle_o2(char **fmt, va_list args, t_fmt *fl);
ssize_t				pf_handle_u(char **fmt, va_list args, t_fmt *fl);
ssize_t				pf_handle_u2(char **fmt, va_list args, t_fmt *fl);
ssize_t				pf_handle_x(char **fmt, va_list args, t_fmt *fl);
ssize_t				pf_handle_p(char **fmt, va_list args, t_fmt *fl);
ssize_t				pf_handle_c(char **fmt, va_list args, t_fmt *fl);
ssize_t				pf_handle_s(char **fmt, va_list args, t_fmt *fl);
ssize_t				pf_handle_wc(char **fmt, va_list args, t_fmt *fl);
ssize_t				pf_handle_ws(char **fmt, va_list args, t_fmt *fl);

/*
**	Set up Handlers
*/
t_handle			pf_get_handler(char c);
void				pf_setup_fl(t_handle *handlers);

/*
**	Print functions
*/
size_t				pf_getnbr_len(intmax_t nbr, char *base);
size_t				pf_calclen(uintmax_t nbr, t_fmt *fl, char *base, char *pfx);
void				pf_putnbr_base(uintmax_t nbr, char *base);
ssize_t				pf_pad(unsigned int strlen, unsigned int width, int c);
ssize_t				pf_force_pfx(char *prefix, t_fmt *fl, uintmax_t nbr,
						char *base);
ssize_t				pf_printnbr(char *pfx, t_fmt *fl, intmax_t nbr, char *base);
void				pf_print(char **fmt, va_list args, ssize_t *ret);

/*
**	Parse Flags
*/
char				*pf_parse_fl(char *fmt, t_fmt *fl);
char				*pf_parse_width(char *fmt, t_fmt *fl, va_list args);
char				*pf_parse_precision(char *fmt, va_list args, t_fmt *fl);
char				*pf_parse_length(char *fmt, t_fmt *fl);

/*
**	Helper Functions
*/
intmax_t			pf_get_signed(va_list args, t_fmt *fl);
uintmax_t			pf_get_unsigned(va_list args, t_fmt *fl);
char				*pf_check_fl(char *fmt, va_list args, t_fmt *flag);
int					is_instr(char c, char *str);
int					is_end(char c);
void				skip_numb(char **fmt);

/*
**	 ft_printf
*/
ssize_t				ft_printf(char *fmt, ...);
#endif
