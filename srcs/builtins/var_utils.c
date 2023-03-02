/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 02:33:30 by julmuntz          #+#    #+#             */
/*   Updated: 2023/03/01 23:23:21 by julmuntz         ###   ########.fr       */
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
		current->next = (t_export *)galloc(NULL, sizeof(t_export), d);
		if (!current->next)
			return (1);
		current->next->key = d->x->new_key;
		current->next->value = d->x->new_value;
		current->next->next = NULL;
		d->env_size++;
	}
	return (0);
}

int	update_var(t_export *current, t_data *d, char *arg, int *plus)
{
	char	*add;

	add = NULL;
	if (*plus == 1)
	{
		if (!current->value)
		{
			add = galloc(ft_strdup(d->x->new_value), sizeof(char)
					* ft_strlen(d->x->new_value) + 1, d);
		}
		else
		{
			add = galloc(ft_strjoin(current->value, d->x->new_value),
					sizeof(char) * (ft_strlen(current->value)
						+ ft_strlen(d->x->new_value)) + 1, d);
		}
		current->value = add;
	}
	else if (ft_strchr(arg, '=')
		&& ft_strcmp(current->value, d->x->new_value))
		current->value = d->x->new_value;
	return (0);
}

static int	get_var3(t_data *d, char *arg, int *i)
{
	if (arg && arg[*i] != '=')
	{
		if (ft_strcmp(arg, d->x->key))
		{
			d->x->new_key = galloc(ft_strdup(arg),
					sizeof(char) * ft_strlen(arg) + 1, d);
			if (!d->x->new_key)
				return (1);
		}
		d->x->new_value = NULL;
	}
	return (0);
}

static int	get_var2(t_data *d, char *arg, int *plus, int *i)
{
	if (arg && arg[*i] == '=' && d->x->key && d->x->value)
	{
		if (ft_strncmp(arg, d->x->key, *i - *plus))
		{
			d->x->new_key = galloc(ft_strndup(arg, *i - *plus), sizeof(char)
					* (*i - *plus) + 1, d);
			if (!d->x->new_key)
				return (1);
		}
		if (ft_strcmp(arg + *i + 1, d->x->value))
		{
			d->x->new_value = galloc(ft_strdup(arg + *i + 1), sizeof(char)
					* ft_strlen(arg + *i + 1) + 1, d);
			if (!d->x->new_value)
				return (1);
		}
	}
	else if (get_var3(d, arg, i))
		return (1);
	return (0);
}

int	get_var(t_data *d, char *arg, int *plus)
{
	int	i;

	i = 0;
	while (arg[i] != '=' && arg[i])
	{
		if (arg[i] == '+')
			(*plus)++;
		i++;
	}
	if (*plus > 1 || *arg == '=' || *arg == '+')
		return (ft_fprintf(STDERR_FILENO,
				"minishell: export: `%s\': not a valid identifier\n",
				arg), 0);
	if (get_var2(d, arg, plus, &i))
		return (1);
	return (0);
}
