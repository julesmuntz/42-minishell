/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:21:43 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/12 02:51:08 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_env(t_builtins *data, t_export *node)
{
	t_export	*current;

	(void)data;
	current = node;
	if (!data->cmd[1])
	{
		while (current != NULL)
		{
			printf("%s\n", current->line_env);
			current = current->next;
		}
	}
	else
	{
		printf("env: '%s': No such file or directory\n", data->cmd[1]);
		return (0);
	}
	return (0);
}
