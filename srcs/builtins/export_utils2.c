/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 18:39:31 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/10 18:51:44 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	xprt_size(t_export *node)
{
	int		count;

	count = 0;
	if (!node)
		return (0);
	while (node)
	{
		node = node->next;
		count++;
	}
	return (count);
}

t_export	*sort_xprt(t_export* lst)
{
	t_export	*top;
	char		*swap;

	top = lst;
	while (lst->next)
	{
		if (!ft_strcmp(lst->str, lst->next->str))
		{
			swap = lst->str;
			lst->str = lst->next->str;
			lst->next->str = swap;
			lst = top;
		}
		else
			lst = lst->next;
	}
	lst = top;
	return (lst);
}

char	*xprt_pop(t_export **ptr)
{
	t_export	*next_node;
	char		*res;

	next_node = NULL;
	res = 0;
	if (*ptr == NULL)
		return (0);
	next_node = (*ptr)->next;
	res = (*ptr)->str;
	free(*ptr);
	*ptr = next_node;
	return (res);
}

void	xprt_pop_last(t_export **ptr)
{
	t_export	*node;

	if (!*ptr || !(*ptr)->next)
		return ;
	node = *ptr;
	while (node->next->next)
		node = node->next;
	node->next->next = *ptr;
	*ptr = node->next;
	node->next = NULL;
}

t_export	*xprt_last(t_export *node)
{
	if (node == NULL)
		return (NULL);
	while (node->next)
		node = node->next;
	return (node);
}
