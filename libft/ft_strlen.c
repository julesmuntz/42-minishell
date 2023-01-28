/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:23:22 by julmuntz          #+#    #+#             */
/*   Updated: 2022/05/19 16:21:24 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strnlen(char *str, size_t maxlen)
{
	char	*ptr;

	ptr = str;
	while (maxlen-- > 0 && *ptr)
		ptr++;
	return (ptr - str);
}
