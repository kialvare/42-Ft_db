/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 23:01:12 by kcheung           #+#    #+#             */
/*   Updated: 2016/12/13 10:28:31 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*mapped_str;
	char	*temp;

	if (!s ||
		!f ||
		!(mapped_str = ft_strdup(s)))
		return (0);
	temp = mapped_str;
	while (*temp)
	{
		*temp = f(*temp);
		++temp;
	}
	return (mapped_str);
}
