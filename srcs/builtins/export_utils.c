/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:57:26 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/25 22:37:48 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	malloc_key_value(t_export *node, char *ptr, char *line, t_data *d)
{
	int	key_len;
	int	value_len;

	key_len = ptr - line;
	value_len = ft_strlen(line) - key_len - 1;
	node->key = (char *)malloc(key_len + 1);
	if (!node->key)
		return (1);
	garbage_collector(node->key, d);
	ft_strncpy(node->key, line, key_len);
	node->key[key_len] = '\0';
	node->value = (char *)malloc(value_len + 1);
	if (!node->value)
		return (1);
	garbage_collector(node->value, d);
	ft_strncpy(node->value, ptr + 1, value_len);
	node->value[value_len] = '\0';
	return (0);
}

static t_export	*init_export2(char *line, t_data *d)
{
	t_export	*node;
	char		*ptr;

	node = (t_export *)malloc(sizeof(t_export));
	if (!node)
		return (NULL);
	garbage_collector(node, d);
	ptr = ft_strchr(line, '=');
	if (!ptr)
		return (NULL);
	node->key = NULL;
	node->value = NULL;
	node->new_key = NULL;
	node->new_value = NULL;
	if (malloc_key_value(node, ptr, line, d))
		return (NULL);
	node->next = NULL;
	return (node);
}

t_export	*init_export(t_data *d)
{
	t_export	*list;
	t_export	*tail;
	t_export	*node;
	int			i;

	list = NULL;
	tail = NULL;
	i = 0;
	while (d->env[i])
	{
		node = init_export2(d->env[i], d);
		if (!node)
			return (NULL);
		if (!list)
			list = node;
		else
			tail->next = node;
		tail = node;
		i++;
	}
	return (list);
}
