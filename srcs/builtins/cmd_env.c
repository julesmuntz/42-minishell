/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:21:43 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/13 00:21:30 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_env(t_data *d, t_lst *l)
{
	t_export	*current;
	int			i;

	current = d->x;
	(void)current;
	if (!l->arg[1])
	{
		i = 0;
		while (d->env[i])
		{
			printf("%s\n", d->env[i]);
			i++;
		}
	}
	else
		printf("env: '%s': No such file or directory\n", l->arg[1]);
}
