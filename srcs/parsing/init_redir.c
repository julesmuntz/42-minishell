/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 22:18:46 by mbenicho          #+#    #+#             */
/*   Updated: 2023/03/14 21:28:02 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*dup_without_quotes(char *s)
{
	char	*str;

	if (remove_quotes(s, &str))
		return (NULL);
	return (str);
}

static int	init_redir2(t_redir **tab, t_tok *t, int size)
{
	int		i;
	t_tok	*tmp;

	i = 0;
	tmp = t;
	while (i < size)
	{
		(*tab)[i].type = 0;
		if (!ft_strcmp(tmp->str, ">>"))
			(*tab)[i].type = 1;
		if (!ft_strcmp(tmp->str, "<"))
			(*tab)[i].type = 2;
		if (!ft_strcmp(tmp->str, "<<"))
			(*tab)[i].type = 3;
		tmp = tmp->next;
		(*tab)[i].str = dup_without_quotes(tmp->str);
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
