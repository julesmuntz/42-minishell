/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 21:21:04 by julmuntz          #+#    #+#             */
/*   Updated: 2023/01/28 21:24:37 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_arrstrlen(char **s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
		i++;
	return (i);
}

size_t	ft_arrnbrlen(int *n)
{
	size_t	i;

	i = 0;
	if (n == NULL)
		return (0);
	while (n[i])
		i++;
	return (i);
}
