/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 18:54:10 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/12 01:48:51 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort_export(t_export *node)
{
	t_export	*current;
	t_export	*next;
	char		*swap;

	if (node == NULL)
		return ;
	current = node;
	while (current)
	{
		next = current->next;
		while (next)
		{
			if (ft_strcmp(current->line_export, next->line_export) > 0)
			{
				swap = current->line_export;
				current->line_export = next->line_export;
				next->line_export = swap;
			}
			next = next->next;
		}
		current = current->next;
	}
}

int	cmd_export(t_builtins *data, t_export *node)
{
	t_export	*current;

	sort_export(node);
	current = node;
	if (!data->cmd[1])
	{
		while (current != NULL)
		{
			printf("%s\n", current->line_export);
			current = current->next;
		}
	}
	return (0);
}
