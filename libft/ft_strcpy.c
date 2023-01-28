/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 14:48:06 by julmuntz          #+#    #+#             */
/*   Updated: 2022/09/27 10:50:40 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = 0;
	return (s1);
}

size_t	ft_strlcpy(char *dst, char *src, size_t size)
{
	size_t	i[2];

	i[0] = 0;
	i[1] = 0;
	while (src[i[1]])
		i[1]++;
	if (size <= 0)
		return (i[1]);
	while (src[i[0]] && i[0] < size - 1)
	{
		dst[i[0]] = src[i[0]];
		i[0]++;
	}
	dst[i[0]] = 0;
	return (i[1]);
}
