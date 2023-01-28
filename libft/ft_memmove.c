/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:19:29 by julmuntz          #+#    #+#             */
/*   Updated: 2022/05/20 17:15:15 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, void *src, size_t n)
{
	unsigned char	*s;
	unsigned char	*d;

	if (dst < src || src + n <= dst)
		return (ft_memcpy(dst, src, n));
	if (dst > src)
	{
		s = src + n;
		d = dst + n;
		while (n--)
			*--d = *--s;
	}
	return (dst);
}
