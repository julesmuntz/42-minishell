/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenicho <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 22:18:46 by mbenicho          #+#    #+#             */
/*   Updated: 2023/02/05 22:18:46 by mbenicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_redir2(t_redir **tab, t_tok *t, int size)
{
	int		i;
	t_tok	*tmp;

	i = 0;
	tmp = t;
	while (i < size)
	{
		(*tab)[i].type = 0;
		if (ft_strlen(tmp->str) == 2)
			(*tab)[i].type = 1;
		tmp = tmp->next;
		(*tab)[i].str = ft_strdup(tmp->str);
		if (!(*tab)->str)
			return (1);
		tmp = tmp->next;
		i++;
	}
	(*tab)[i].str = NULL;
	return (0);
}

int	init_redir(t_redir **tab, t_tok *t)
{
	int		size;

	if (t)
	{
		size = ft_tok_size(t) / 2;
		*tab = malloc((size + 1) * sizeof(t_redir));
		if (!*tab)
			return (free_tok(t), 1);
		if (init_redir2(tab, t, size))
			return (free_tok(t), ft_free_redir(*tab), *tab = NULL, 1);
	}
	return (free_tok(t), 0);
}
