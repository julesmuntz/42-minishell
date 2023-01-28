/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:57:22 by julmuntz          #+#    #+#             */
/*   Updated: 2022/11/04 01:02:22 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_sqrt(int nbr)
{
	int	res;
	int	tmp;

	res = nbr / 2;
	tmp = 0;
	while (res != tmp)
	{
		tmp = res;
		res = (nbr / tmp + tmp) / 2;
	}
	return (res);
}
