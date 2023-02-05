/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tok_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenicho <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 22:18:46 by mbenicho          #+#    #+#             */
/*   Updated: 2023/02/05 22:18:46 by mbenicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_size(t_tok *t)
{
	int	i;

	i = 1;
	while (t)
	{
		i += (ft_strlen(t->str));
		t = t->next;
	}
	return (i);
}

int	ft_tok_join(t_tok *t, char **str)
{
	int		i;
	int		j;
	t_tok	*tmp;

	*str = malloc(count_size(t) * sizeof(char));
	if (!*str)
		return (1);
	i = 0;
	tmp = t;
	while (tmp)
	{
		j = 0;
		while (tmp->str[j])
		{
			(*str)[i] = tmp->str[j];
			j++;
			i++;
		}
		tmp = tmp->next;
	}
	(*str)[i] = 0;
	return (0);
}
