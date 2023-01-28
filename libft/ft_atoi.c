/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 17:01:44 by julmuntz          #+#    #+#             */
/*   Updated: 2022/06/02 22:19:07 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(char *str)
{
	int		i[2];
	long	result;

	i[0] = 0;
	i[1] = 1;
	result = 0;
	while ((str[i[0]] == ' ') || (str[i[0]] >= '\t' && str[i[0]] <= '\r'))
		i[0]++;
	if (str[i[0]] == '-')
	{
		i[1] *= -1;
		i[0]++;
	}
	else if (str[i[0]] == '+')
		i[0]++;
	while (str[i[0]] >= '0' && str[i[0]] <= '9')
	{
		result = result * 10 + str[i[0]] - 48;
		if ((unsigned long)result > INT_MAX && i[1] == 1)
			return (-1);
		if ((unsigned long)result > 2147483648 && i[1] == -1)
			return (0);
		i[0]++;
	}
	return (result * i[1]);
}
