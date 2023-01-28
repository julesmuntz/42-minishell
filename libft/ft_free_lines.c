/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_lines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 15:30:51 by julmuntz          #+#    #+#             */
/*   Updated: 2022/11/20 15:34:15 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_lines(char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}
