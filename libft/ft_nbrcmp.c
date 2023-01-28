/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 15:40:51 by julmuntz          #+#    #+#             */
/*   Updated: 2022/09/29 17:49:15 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nbrcmp(int *array, int size)
{
	int	i;
	int	next;

	if (!array)
		return (0);
	i = 0;
	while (i < size - 1)
	{
		next = i + 1;
		while (next < size - 1)
		{
			if (array[i] == array[next])
				return (TRUE);
			next++;
		}
		i++;
	}
	return (FALSE);
}
