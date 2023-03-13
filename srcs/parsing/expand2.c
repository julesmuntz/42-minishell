/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:43:47 by mbenicho          #+#    #+#             */
/*   Updated: 2023/03/13 15:44:07 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	separate_quotes(t_tok **t, char *s)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
	{
		j = parse_quotes(s + i);
		if (j)
			j++;
		if (j == 0)
		{
			while (s[i + j])
			{
				if (is_quotes(s, i, j))
					break ;
				j++;
			}
			if (j && new_tok(t, s + i, j))
				return (free_tok(*t), 1);
		}
		else if (j && new_tok(t, s + i, j))
			return (free_tok(*t), 1);
		i += j;
	}
	return (0);
}
