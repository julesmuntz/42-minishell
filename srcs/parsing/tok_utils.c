/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:19:46 by mbenicho          #+#    #+#             */
/*   Updated: 2023/02/02 14:05:53 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tok_size(t_tok *t)
{
	int	i;

	i = 0;
	while (t)
	{
		t = t->next;
		i++;
	}
	return (i);
}

void	ft_tok_add_back(t_tok **t, t_tok *new)
{
	t_tok	*tmp;

	tmp = *t;
	if (!*t)
		*t = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int	new_tok(t_tok **t, char *str, int j)
{
	t_tok	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (1);
	new->str = malloc((j + 1) * sizeof(char));
	if (!new->str)
		return (free(new), 1);
	ft_strlcpy(new->str, str, j + 1);
	new->next = NULL;
	ft_tok_add_back(t, new);
	return (0);
}

void	free_tok(t_tok *t)
{
	t_tok	*tmp;

	if (!t)
		return ;
	while (t)
	{
		tmp = t;
		t = t->next;
		free(tmp->str);
		free(tmp);
	}
}

void	tok_extract(t_tok **t, t_tok **dest, t_tok *elem)
{
	t_tok	*tmp;

	tmp = *t;
	ft_tok_add_back(dest, elem);
	if (*t == elem)
		*t = (*t)->next;
	else
	{
		while (tmp->next != elem)
			tmp = tmp->next;
		tmp->next = elem->next;
	}
	elem->next = NULL;
}

void	token_to_array(t_tok *head, char **array)
{
	t_tok	*current;
	int		i;

	current = head;
	i = 0;
	while (current)
	{
		array[i] = current->str;
		current = current->next;
		i++;
	}
}
