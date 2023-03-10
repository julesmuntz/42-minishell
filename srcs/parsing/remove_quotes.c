/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 22:18:46 by mbenicho          #+#    #+#             */
/*   Updated: 2023/03/13 15:45:07 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quotes(char *s, int i, int j)
{
	if ((s[i + j] == '"' || s[i + j] == '\'') && parse_quotes(s + i + j))
		return (1);
	return (0);
}

static int	isolate_quotes(t_tok **t, char *s)
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
		else if (j && new_tok(t, s + i + 1, j - 2))
			return (free_tok(*t), 1);
		i += j;
	}
	return (0);
}

int	remove_quotes(char *s, char **str)
{
	t_tok	*t;

	t = NULL;
	if (isolate_quotes(&t, s))
		return (1);
	if (ft_tok_join(t, str))
		return (free_tok(t), 1);
	free_tok(t);
	return (0);
}
