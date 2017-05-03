/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insertsort_int.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 14:31:01 by kcheung           #+#    #+#             */
/*   Updated: 2017/02/26 14:31:38 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_insertsort_int(size_t len, int *array)
{
	size_t	i;
	size_t	j;
	int		element;

	i = 1;
	while (i < len - 1)
	{
		element = array[i];
		j = i;
		while (j > 0 && array[j - 1] > element)
		{
			array[j] = array[j - 1];
			j = j - 1;
		}
		array[j] = element;
		i++;
	}
}
