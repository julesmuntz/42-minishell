/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 18:54:10 by julmuntz          #+#    #+#             */
/*   Updated: 2023/03/16 15:06:00 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_export(t_export *current, t_data *d, t_lst *l)
{
	t_export	*sorted;
	t_export	*tmp;

	if (!l->arg[1])
	{
		sorted = NULL;
		copy_export(current, &sorted, d);
		sort_export(&sorted);
		tmp = sorted;
		while (tmp)
		{
			if (ft_strcmp(tmp->key, "_") && ft_strcmp(tmp->value, getenv("_")))
			{
				if (tmp->key && !tmp->value)
					ft_fprintf(d->out, "declare -x %s\n", tmp->key);
				else if (tmp->key && tmp->value)
					ft_fprintf(d->out, "declare -x %s=\"%s\"\n", tmp->key,
						tmp->value);
			}
			tmp = tmp->next;
		}
		return (0);
	}
	return (0);
}

static int	export_var(t_export *current, t_data *d, char *arg)
{
	int	plus;
	int	found;

	if (!ft_str_iskey(arg) || *arg == '\0' || *arg == '=' || *arg == '+')
		return (g_exit_code = 1, ft_fprintf(STDERR_FILENO,
				"minishell: export: `%s\': not a valid identifier\n", arg), 0);
	plus = 0;
	found = 0;
	current = d->x;
	if (get_var(d, arg, &plus))
		return (1);
	while (current)
	{
		if (!ft_strcmp(current->key, d->x_key) && d->x_key)
		{
			found = 1;
			if (update_var(current, d, arg, &plus))
				return (1);
			break ;
		}
		current = current->next;
	}
	if (create_var(current, d, found))
		return (1);
	return (0);
}

int	cmd_export(t_data *d, t_lst *l)
{
	t_export	*current;
	int			i;

	i = 0;
	current = d->x;
	g_exit_code = 0;
	if (l->arg[1])
	{
		while (l->arg[++i])
			if (export_var(current, d, l->arg[i]))
				return (1);
	}
	if (!l->arg[1])
		if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
			return (0);
	print_export(current, d, l);
	return (0);
}
