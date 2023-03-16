/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 02:33:30 by julmuntz          #+#    #+#             */
/*   Updated: 2023/03/16 15:10:27 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_var(t_export *current, t_data *d, int found)
{
	t_export	*new;

	current = d->x;
	if (!found)
	{
		while (current && current->next)
			current = current->next;
		new = galloc(NULL, sizeof(t_export), d);
		if (!new)
			return (1);
		new->key = d->x_key;
		new->value = d->x_value;
		new->next = NULL;
		if (current)
			current->next = new;
		else
			d->x = new;
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
			add = galloc(ft_strdup(d->x_value), sizeof(char)
					* ft_strlen(d->x_value) + 1, d);
		}
		else
		{
			add = galloc(ft_strjoin(current->value, d->x_value),
					sizeof(char) * (ft_strlen(current->value)
						+ ft_strlen(d->x_value)) + 1, d);
		}
		current->value = add;
	}
	else if (ft_strchr(arg, '=')
		&& ft_strcmp(current->value, d->x_value))
		current->value = d->x_value;
	return (0);
}

static int	get_var3(t_data *d, char *arg, int *i)
{
	if (arg && arg[*i] != '=')
	{
		d->x_key = galloc(ft_strdup(arg),
				sizeof(char) * ft_strlen(arg) + 1, d);
		if (!d->x_key)
			return (1);
		d->x_value = NULL;
	}
	return (0);
}

static int	get_var2(t_data *d, char *arg, int *plus, int *i)
{
	if (arg && arg[*i] == '=')
	{
		d->x_key = galloc(ft_strndup(arg, *i - *plus), sizeof(char)
				* (*i - *plus) + 1, d);
		if (!d->x_key)
			return (1);
		d->x_value = galloc(ft_strdup(arg + *i + 1), sizeof(char)
				* ft_strlen(arg + *i + 1) + 1, d);
		if (!d->x_value)
			return (1);
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
	if (*plus > 1)
		return (g_exit_code = 1, ft_fprintf(STDERR_FILENO,
				"minishell: export: `%s\': not a valid identifier\n",
				arg), 0);
	if (get_var2(d, arg, plus, &i))
		return (1);
	return (0);
}
