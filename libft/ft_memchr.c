/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 16:31:08 by julmuntz          #+#    #+#             */
/*   Updated: 2022/05/30 15:09:50 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void *s, int c, size_t n)
{
	size_t	i;
	char	chr;
	char	*str;

	i = 0;
	chr = (char)c;
	str = (char *)s;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (str[i] == chr)
			return ((void *)str + i);
		i++;
	}
	return (NULL);
}
