/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 12:34:04 by kcheung           #+#    #+#             */
/*   Updated: 2016/11/11 12:34:06 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	beg_index(char *s)
{
	int i;

	i = 0;
	while (*s == ' ' || *s == '\t' || *s == '\n')
	{
		i++;
		s++;
	}
	return (i);
}

static	int	end_index(char *s)
{
	int i;

	i = ft_strlen(s) - 1;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
	{
		i--;
	}
	return (i);
}

char		*ft_strtrim(char const *s)
{
	char			*str;
	int				beg;
	int				end;
	int				j;
	unsigned int	len;

	if (!s)
		return (NULL);
	beg = beg_index((char *)s);
	end = end_index((char *)s);
	j = 0;
	len = end - beg;
	if (!(str = (char *)malloc(sizeof(char) * len + 2)))
		return (NULL);
	while (beg <= end)
	{
		str[j] = s[beg];
		beg++;
		j++;
	}
	str[j] = '\0';
	return (str);
}
