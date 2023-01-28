/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 13:59:37 by julmuntz          #+#    #+#             */
/*   Updated: 2022/05/20 17:12:21 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *full, char *part, size_t len)
{
	size_t	i;
	size_t	l;

	i = 0;
	l = 0;
	if (*part == 0)
		return ((char *)full);
	if (*full == 0 && *part == 0)
		return ("");
	while (full[i] && i < len)
	{
		while (full[i + l] == part[l] && (i + l < len))
		{
			l++;
			if (part[l] == 0)
				return ((char *)full + i);
		}
		l = 0;
		i++;
	}
	return (NULL);
}

char	*ft_strrstr(char *full, char *part, size_t len)
{
	size_t	size;
	char	*cmp;

	size = 0;
	while (full[size])
		size++;
	cmp = full + size - len;
	while (cmp >= full)
	{
		if (ft_strncmp(cmp, part, len) == 0)
			return (cmp);
		cmp--;
	}
	return (NULL);
}
