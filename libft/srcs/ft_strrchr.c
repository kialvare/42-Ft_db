/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 00:04:38 by kcheung           #+#    #+#             */
/*   Updated: 2016/11/05 00:04:39 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *temp;
	char *ptr;

	temp = (char *)s;
	ptr = NULL;
	while (*temp)
	{
		if (*temp == c)
			ptr = temp;
		temp++;
	}
	if (c == '\0')
		return (temp);
	else if (ptr == NULL)
		return (NULL);
	else
		return (ptr);
}
