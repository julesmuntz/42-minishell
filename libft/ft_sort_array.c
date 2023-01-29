/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:31:18 by julmuntz          #+#    #+#             */
/*   Updated: 2022/09/29 14:49:13 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*ft_sort_arrnbr(int *tab, int size)
{
	int	temporary;
	int	index[2];

	index[0] = 0;
	while (index[0] < size)
	{
		index[1] = index[0] + 1;
		while (index[1] < size - 1)
		{
			if (tab[index[0]] > tab[index[1]])
			{
				temporary = tab[index[0]];
				tab[index[0]] = tab[index[1]];
				tab[index[1]] = temporary;
			}
			index[1]++;
		}
		index[0]++;
	}
	return (tab);
}

char	**ft_sort_arrstr(char **tab, int size)
{
	int	index[2];

	index[0] = 0;
	while (index[0] < size)
	{
		index[1] = index[0] + 1;
		while (index[1] < size - 1)
		{
			if (*tab[index[0]] > *tab[index[1]])
				ft_swap(tab[index[0]], tab[index[1]]);
			index[1]++;
		}
		index[0]++;
	}
	return (tab);
}
