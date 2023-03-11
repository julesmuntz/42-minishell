/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 12:23:06 by julmuntz          #+#    #+#             */
/*   Updated: 2023/03/11 13:33:13 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_isspace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!((str[i] == '\0')
				|| (str[i] >= '\t' && str[i] <= '\r')
				|| (str[i] == ' ')))
			return (0);
		i++;
	}
	return (1);
}

int	ft_str_iskey(char *str)
{
	int	i;

	if (*str >= '0' && *str <= '9')
		return (0);
	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
	{
		if (!((str[i] >= 'A' && str[i] <= 'Z')
				|| (str[i] >= 'a' && str[i] <= 'z')
				|| (str[i] >= '0' && str[i] <= '9')
				|| (str[i] == '_')))
			return (0);
		i++;
	}
	if (str[i] == '+')
		i++;
	if (str[i] == '\0' || str[i] == '=')
		return (1);
	return (0);
}
