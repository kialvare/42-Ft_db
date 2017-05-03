/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 13:10:49 by kcheung           #+#    #+#             */
/*   Updated: 2017/04/07 10:41:47 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_word_count(const char *s, char c)
{
	int	result;
	int	i;

	i = 0;
	result = 0;
	while (s[i] && (s[i] == c))
		i++;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			while (s[i] && s[i] != c)
				i++;
			result++;
		}
	}
	return (result);
}

char	**ft_strsplit(const char *str, char c)
{
	char	**tab;
	int		i;
	int		n;
	int		start;

	if (!str ||
		!(tab = (char **)malloc(sizeof(char*) * (ft_word_count(str, ' ') + 1))))
		return (NULL);
	i = 0;
	n = 0;
	while (str[i])
	{
		if (str[i] && str[i] == c)
			i++;
		else
		{
			start = i;
			while (str[i] && str[i] != c)
				i++;
			tab[n] = ft_strsub(str, start, i - start);
			n++;
		}
	}
	tab[n] = 0;
	return (tab);
}
