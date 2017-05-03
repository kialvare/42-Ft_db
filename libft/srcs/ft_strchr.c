/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 23:46:44 by kcheung           #+#    #+#             */
/*   Updated: 2016/11/04 23:46:46 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char *temp;

	temp = (char *)s;
	while (*temp)
	{
		if (*temp == c)
			return (temp);
		else
			temp++;
	}
	if (c == '\0')
		return (temp);
	return (NULL);
}
