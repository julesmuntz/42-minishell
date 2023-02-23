/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 02:33:30 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/23 19:58:15 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_var(t_export *current, t_data *d, int found)
{
	current = d->x;
	if (!found)
	{
		while (current->next)
			current = current->next;
		current->next = (t_export *)malloc(sizeof(t_export));
		if (!current->next)
			return (1);
		current->next->key = d->x->new_key;
		current->next->value = d->x->new_value;
		current->next->next = NULL;
	}
	return (0);
}

int	update_var(t_export *current, t_data *d, int *plus)
{
	char	*add;

	add = NULL;
	if (*plus == 1)
	{
		if (!current->value && !ft_strdup_safe(d->x->new_value))
			return (1);
		else
		{
			add = ft_strjoin(current->value, d->x->new_value);
			if (!add)
				return (1);
			ft_strdel(&current->value);
		}
		ft_strdel(&d->x->new_value);
		current->value = add;
	}
	else if (ft_strchr(d->l->arg[1], '=')
		&& ft_strcmp(current->value, d->x->new_value))
	{
		ft_strdel(&current->value);
		current->value = d->x->new_value;
	}
	return (0);
}

static int	get_var3(t_data *d, t_lst *l, int *i)
{
	if (l->arg[1] && l->arg[1][*i] != '=')
	{
		if (ft_strcmp(l->arg[1], d->x->new_key))
		{
			d->x->new_key = ft_strdup(l->arg[1]);
			if (!d->x->new_key)
				return (1);
		}
		d->x->new_value = NULL;
	}
	return (0);
}

static int	get_var2(t_data *d, t_lst *l, int *plus, int *i)
{
	if (l->arg[1] && l->arg[1][*i] == '=' && d->x->key && d->x->value)
	{
		if (ft_strncmp(l->arg[1], d->x->new_key, *i - *plus))
		{
			d->x->new_key = ft_strndup(l->arg[1], *i - *plus);
			if (!d->x->new_key)
				return (1);
		}
		if (ft_strcmp(l->arg[1] + *i + 1, d->x->new_value))
		{
			d->x->new_value = ft_strdup(l->arg[1] + *i + 1);
			if (!d->x->new_value)
				return (1);
		}
	}
	else if (get_var3(d, l, i))
		return (1);
	return (0);
}

int	get_var(t_data *d, t_lst *l, int *plus)
{
	int	i;

	i = 0;
	while (l->arg[1][i] != '=' && l->arg[1][i])
	{
		if (l->arg[1][i] == '+')
			(*plus)++;
		i++;
	}
	if (*plus > 1)
		return (ft_fprintf(STDERR_FILENO,
				"minishell: export: `%s\': not a valid identifier\n",
				l->arg[1]), 1);
	if (get_var2(d, l, plus, &i))
		return (1);
	return (0);
}
