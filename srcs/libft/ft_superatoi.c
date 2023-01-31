/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_superatoi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenicho <mbenicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:18:10 by mbenicho          #+#    #+#             */
/*   Updated: 2023/01/31 19:18:34 by mbenicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_superatoi(char *nptr, int *res)
{
	long	n;
	int		sign;
	int		nb;

	n = 0;
	sign = 1;
	if (*nptr == '-' || *nptr == '\0')
		return (1);
	while (*nptr >= '0' && *nptr <= '9')
	{
		nb = (n * 10);
		if (nb / 10 != n)
			return (1);
		n = (long)nb + *nptr - '0';
		if (n * sign > INT_MAX || n * sign < INT_MIN)
			return (1);
		nptr++;
	}
	if (*nptr)
		return (1);
	*res = n * sign;
	return (0);
}
