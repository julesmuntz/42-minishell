/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 12:46:26 by julmuntz          #+#    #+#             */
/*   Updated: 2022/05/19 16:21:24 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *s)
{
	char	*d;
	char	*t;

	if (s == NULL)
		return (NULL);
	d = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (d == NULL)
		return (NULL);
	t = d;
	while (*s)
		*t++ = *s++;
	*t = 0;
	return (d);
}
