/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:57:26 by julmuntz          #+#    #+#             */
/*   Updated: 2023/03/16 15:06:41 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_export(t_export *src, t_export **dst, t_data *d)
{
	t_export	*new;
	t_export	**ptr;

	while (src)
	{
		new = (t_export *)galloc(NULL, sizeof(t_export), d);
		new->key = galloc(ft_strdup(src->key),
				sizeof(char) * ft_strlen(src->key) + 1, d);
		if (!new->key)
			return ;
		new->value = NULL;
		if (src->value)
			new->value = galloc(ft_strdup(src->value),
					sizeof(char) * ft_strlen(src->value) + 1, d);
		ptr = dst;
		while (*ptr && ft_strcmp((*ptr)->key, new->key) < 0)
			ptr = &((*ptr)->next);
		new->next = *ptr;
		*ptr = new;
		src = src->next;
	}
}

void	sort_export(t_export **node)
{
	t_export	*current;
	t_export	*sorted;
	t_export	*next;

	sorted = NULL;
	while (*node != NULL)
	{
		current = *node;
		*node = (*node)->next;
		if (sorted == NULL || ft_strcmp(current->key, sorted->key) < 0)
		{
			current->next = sorted;
			sorted = current;
		}
		else
		{
			next = sorted;
			while (next->next != NULL && ft_strcmp(current->key,
					next->next->key) >= 0)
				next = next->next;
			current->next = next->next;
			next->next = current;
		}
	}
	*node = sorted;
}

static int	malloc_key_value(t_export *node, char *ptr, char *line, t_data *d)
{
	int	key_len;
	int	value_len;

	key_len = ptr - line;
	value_len = ft_strlen(line) - key_len - 1;
	node->key = (char *)galloc(NULL, key_len + 1, d);
	if (!node->key)
		return (1);
	ft_strncpy(node->key, line, key_len);
	node->key[key_len] = '\0';
	node->value = (char *)galloc(NULL, value_len + 1, d);
	if (!node->value)
		return (1);
	ft_strncpy(node->value, ptr + 1, value_len);
	node->value[value_len] = '\0';
	return (0);
}

static t_export	*init_export2(char *line, t_data *d)
{
	t_export	*node;
	char		*ptr;

	node = (t_export *)galloc(NULL, sizeof(t_export), d);
	if (!node)
		return (NULL);
	ptr = ft_strchr(line, '=');
	if (!ptr)
		return (NULL);
	node->key = NULL;
	node->value = NULL;
	d->x_key = NULL;
	d->x_value = NULL;
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
	d->env_size = i;
	return (list);
}
