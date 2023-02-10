/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:31:18 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/10 16:55:11 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sort_arrnbr(int *n, int size)
{
	int	temporary;
	int	a;
	int	b;

	a = 0;
	while (a < size)
	{
		b = a + 1;
		while (b < size - 1)
		{
			if (n[a] > n[b])
			{
				temporary = n[a];
				n[a] = n[b];
				n[b] = temporary;
			}
			b++;
		}
		a++;
	}
}

void	ft_sort_arrstr(char **s, int size)
{
	int		a;
	int		b;
	char	*tmp;

	a = 0;
	while (a < size)
	{
		b = a + 1;
		while (b < size)
		{
			if (ft_strcmp(s[a], s[b]) > 0)
			{
				tmp = s[a];
				s[a] = s[b];
				s[b] = tmp;
			}
			b++;
		}
		a++;
	}
}
