/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 18:54:10 by julmuntz          #+#    #+#             */
/*   Updated: 2023/03/16 13:38:42 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_env(t_export *current, t_data *d, t_lst *l)
{
	t_export	*tmp;

	if (!l->arg[1])
	{
		current = d->x;
		while (current)
		{
			if (ft_strcmp(current->key, "_")
				&& ft_strcmp(current->value, getenv("_")) && current->value)
				ft_fprintf(d->out,
					"%s=%s\n", current->key, current->value);
			else if (!ft_strcmp(current->key, "_"))
				tmp = current;
			current = current->next;
		}
		if ((getenv("_")))
			ft_fprintf(d->out,
				"%s=%s\n", tmp->key, tmp->value);
		return (0);
	}
	ft_fprintf(STDERR_FILENO,
		"env: '%s': No such file or directory\n", l->arg[1]);
	g_exit_code = 127;
	return (0);
}

int	cmd_env(t_data *d, t_lst *l)
{
	t_export	*current;

	current = d->x;
	g_exit_code = 0;
	if (!l->arg[1])
		if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
			return (0);
	print_env(current, d, l);
	return (0);
}
