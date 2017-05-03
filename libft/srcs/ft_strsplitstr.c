/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitstr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kialvare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 08:31:31 by kialvare          #+#    #+#             */
/*   Updated: 2017/01/19 08:34:34 by kialvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_startswith(const char *str, const char *delim)
{
	size_t		i;

	i = 0;
	while (i < ft_strlen(str))
	{
		if (delim[i] == '\0')
			return (1);
		if (str[i] == '\0' || str[i] != delim[i])
			return (0);
		i++;
	}
	if (str[i] == delim[i])
		return (1);
	return (0);
}

static int		ft_wordcount(char const *s, char *delim)
{
	int prev;
	int count;

	prev = 0;
	count = 0;
	while (*s)
	{
		if (ft_startswith(s, delim))
		{
			prev = 0;
			s += ft_strlen(delim) - 1;
		}
		else if (prev == 0)
		{
			prev = 1;
			count++;
		}
		s++;
	}
	return (count);
}

char			**ft_strsplitstr(char const *s, char *delim)
{
	int		sholder;
	char	**new_s;
	int		i;
	int		j;
	int		begin;

	i = 0;
	j = -1;
	if (s == 0 || delim == 0)
		return (NULL);
	sholder = ft_wordcount(s, delim);
	if (!(new_s = malloc((sizeof(char*) * (sholder + 1)))))
		return (NULL);
	while (++j < sholder)
	{
		while (s[i] && ft_startswith(s + i, delim))
			i += ft_strlen(delim);
		begin = i;
		while (s[i] && !ft_startswith(s + i, delim))
			i++;
		new_s[j] = ft_strsub(s, begin, i - begin);
	}
	new_s[j] = NULL;
	return (new_s);
}
