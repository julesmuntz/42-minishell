/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 18:27:22 by julmuntz          #+#    #+#             */
/*   Updated: 2023/03/12 18:27:39 by julmuntz         ###   ########.fr       */
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

int	ft_setenv(char *key, char *value, t_data *d)
{
	t_export	*current;

	if (!d)
		return (1);
	current = d->x;
	while (current)
	{
		if (ft_strcmp(key, current->key) == 0)
		{
			current->value = galloc(ft_strdup(value), ft_strlen(value), d);
			return (0);
		}
		current = current->next;
	}
	current = malloc(sizeof(t_export));
	if (!current)
		return (ft_puterr("minishell: malloc failed\n"), 1);
	current->key = ft_strdup(key);
	current->value = ft_strdup(value);
	current->next = d->x;
	d->x = current;
	return (0);
}
