/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 18:54:10 by julmuntz          #+#    #+#             */
/*   Updated: 2023/03/13 18:10:25 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	unset_var(t_export *current, t_data *d, const char *arg)
{
	t_export	*node;
	t_export	*previous;

	node = current;
	previous = NULL;
	if (!arg)
		return (0);
	while (node != NULL)
	{
		if (!ft_strcmp(node->key, arg))
		{
			if (previous == NULL)
				current = node->next;
			else
				previous->next = node->next;
			d->env_size--;
			return (0);
		}
		else
		{
			previous = node;
			node = node->next;
		}
	}
	return (0);
}

int	cmd_unset(t_data *d, t_lst *l)
{
	t_export	*current;
	int			i;

	i = 0;
	current = d->x;
	g_exit_code = 0;
	if (l->arg[1])
	{
		while (l->arg[++i])
			unset_var(current, d, l->arg[i]);
	}
	return (0);
}
