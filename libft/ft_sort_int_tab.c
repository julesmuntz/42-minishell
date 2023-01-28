/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_int_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:31:18 by julmuntz          #+#    #+#             */
/*   Updated: 2022/09/29 14:49:13 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	*ft_sort_int_tab(int *tab, int size)
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
