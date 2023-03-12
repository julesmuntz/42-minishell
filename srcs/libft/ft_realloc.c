/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:30:38 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/28 21:13:30 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	char	*tmp;

	tmp = ptr;
	if (ptr != NULL)
	{
		size += ft_strlen(ptr);
		ptr = ft_calloc(1, size);
		if (!ptr)
			return (NULL);
		ft_strcpy(ptr, tmp);
		free(tmp);
	}
	else
		ptr = ft_calloc(1, size);
	return (ptr);
}
