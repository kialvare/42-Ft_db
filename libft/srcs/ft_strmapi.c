/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 23:32:15 by kcheung           #+#    #+#             */
/*   Updated: 2016/11/10 23:32:16 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ptr;
	char	*temp;
	int		i;

	if (!s ||
		!f ||
		!(ptr = ft_strdup(s)))
		return (0);
	temp = ptr;
	i = 0;
	while (*temp)
	{
		*temp = f(i, *temp);
		temp++;
		i++;
	}
	return (ptr);
}
