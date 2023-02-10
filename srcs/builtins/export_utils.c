/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:57:10 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/10 22:18:02 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_export	*xprt_new(char *key, char *value)
{
	t_export	*node;

	node = malloc(sizeof(t_export));
	if (node == NULL)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

void	xprt_add_back(t_export **ptr, t_export *new)
{
	t_export	*end;

	if (*ptr == NULL)
		*ptr = new;
	else
	{
		end = *ptr;
		while (end->next != NULL)
			end = end->next;
		end->next = new;
	}
}

void	xprt_add_front(t_export **ptr, t_export *new)
{
	if (new != *ptr)
	new->next = *ptr;
	*ptr = new;
}

void	xprt_clear(t_export **ptr)
{
	t_export	*tmp;

	while (*ptr)
	{
		tmp = (*ptr)->next;
		free(*ptr);
		*ptr = tmp;
	}
	*ptr = NULL;
}

t_export	*xprt_free(t_export *line)
{
	t_export	*tmp;

	while (line)
	{
		tmp = line;
		line = line->next;
		free(tmp);
	}
	return (NULL);
}
