/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 11:28:39 by kcheung           #+#    #+#             */
/*   Updated: 2017/03/01 16:35:20 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void		pf_setup_fl(t_handle *handlers)
{
	handlers['%'] = &pf_handle_none;
	handlers['d'] = &pf_handle_d;
	handlers['D'] = &pf_handle_d2;
	handlers['i'] = &pf_handle_d;
	handlers['u'] = &pf_handle_u;
	handlers['U'] = &pf_handle_u2;
	handlers['o'] = &pf_handle_o;
	handlers['O'] = &pf_handle_o2;
	handlers['x'] = &pf_handle_x;
	handlers['X'] = &pf_handle_x;
	handlers['c'] = &pf_handle_c;
	handlers['C'] = &pf_handle_wc;
	handlers['s'] = &pf_handle_s;
	handlers['S'] = &pf_handle_ws;
	handlers['p'] = &pf_handle_p;
}

t_handle	pf_get_handler(char c)
{
	t_handle	*handlers;

	handlers = NULL;
	if (handlers == NULL)
	{
		if (!(handlers = (t_handle *)malloc(sizeof(t_handle) * 256)))
			return (NULL);
		ft_bzero(handlers, 256);
		pf_setup_fl(handlers);
	}
	if (!is_instr(c, "%ddDiuUoOxXcCsSp"))
		return (0);
	free(handlers);
	return (handlers[(int)c]);
}
