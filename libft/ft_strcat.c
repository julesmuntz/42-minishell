/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:46:16 by julmuntz          #+#    #+#             */
/*   Updated: 2022/05/20 17:12:00 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, char *src)
{
	int	i[2];

	i[0] = 0;
	while (dest[i[0]])
		i[0]++;
	i[1] = 0;
	while (src[i[1]])
		dest[i[0]++] = src[i[1]++];
	dest[i[0]] = 0;
	return (dest);
}

size_t	ft_strlcat(char *dst, char *src, size_t size)
{
	size_t	len;

	len = ft_strnlen(dst, size);
	if (len == size)
		return (len + ft_strlen(src));
	return (len + ft_strlcpy(dst + len, src, size - len));
}
