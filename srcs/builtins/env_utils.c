/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 18:27:22 by julmuntz          #+#    #+#             */
/*   Updated: 2023/03/15 22:56:19 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *key, t_data *d)
{
	int	i;
	int	key_len;

	key_len = ft_strlen(key);
	i = 0;
	while (d->env[i])
	{
		if (!ft_strncmp(d->env[i], key, key_len) && d->env[i][key_len] == '=')
			return (d->env[i] + key_len + 1);
		i++;
	}
	return (NULL);
}

int	ft_setenv2(char *key, char *value, t_data *d)
{
	t_export	*current;

	current = galloc(NULL, sizeof(t_export), d);
	if (!current)
		return (ft_puterr("minishell: malloc failed\n"), 1);
	current->key = galloc(ft_strdup(key), ft_strlen(key) + 1, d);
	if (value)
		current->value = galloc(ft_strdup(value), ft_strlen(value), d);
	else
		current->value = NULL;
	current->next = d->x;
	d->x = current;
	d->env_size++;
	return (0);
}

int	ft_setenv(char *key, char *value, t_data *d)
{
	t_export	*current;

	current = d->x;
	while (current)
	{
		if (ft_strcmp(key, current->key) == 0)
		{
			if (value)
				current->value = galloc(ft_strdup(value), \
				ft_strlen(value) + 1, d);
			else
				current->value = NULL;
			return (0);
		}
		current = current->next;
	}
	return (ft_setenv2(key, value, d));
}
