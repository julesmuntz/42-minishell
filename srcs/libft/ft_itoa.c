/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:18:24 by mbenicho          #+#    #+#             */
/*   Updated: 2023/03/08 11:18:40 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_convert(int n, char *s, int i)
{
	long long int		nb;
	char				*str;

	nb = n;
	str = s;
	if (nb > 9)
	{
		str = ft_convert(nb / 10, str, i - 1);
		str[i] = (nb % 10) + '0';
	}
	else
		str[i] = nb + '0';
	return (str);
}

static size_t	ft_count(int n)
{
	size_t	size;

	size = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	int		size;
	char	*str;

	size = ft_count(n);
	str = malloc((size + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[size] = 0;
	str = ft_convert(n, str, size - 1);
	return (str);
}
