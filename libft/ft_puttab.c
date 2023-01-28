/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puttab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:47:28 by julmuntz          #+#    #+#             */
/*   Updated: 2022/10/04 12:52:44 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_puttab(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i])
		write(1, &s[i++], 1);
	write(1, "\t", 1);
}

void	ft_puttabs(char *s, int nbr)
{
	int	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i])
		write(1, &s[i++], 1);
	while (nbr--)
		write(1, "\t", 1);
}
