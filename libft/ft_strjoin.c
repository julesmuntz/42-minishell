/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 16:03:50 by julmuntz          #+#    #+#             */
/*   Updated: 2022/06/02 22:21:03 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i[3];
	char	*res;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i[1] = ft_strlen(s1);
	i[2] = ft_strlen(s2);
	res = (char *)malloc(i[1] + i[2] + 1);
	if (res == NULL)
		return (NULL);
	ft_memcpy(res, s1, i[1]);
	ft_memcpy(res + i[1], s2, i[2]);
	res[i[1] + i[2]] = 0;
	return (res);
}
