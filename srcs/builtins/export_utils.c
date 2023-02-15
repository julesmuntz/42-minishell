/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:57:26 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/15 04:04:21 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_export	*copy_export2(t_export *node, t_export *copy, t_export *current)
{
	current->key = ft_strdup(node->key);
	if (!current->key)
		return (free_export(copy), NULL);
	if (node->value)
	{
		current->value = ft_strdup(node->value);
		if (!current->value)
			return (free_export(copy), NULL);
	}
	return (NULL);
}

t_export	*copy_export(t_export *node)
{
	t_export	*copy;
	t_export	*current;

	copy = NULL;
	while (node)
	{
		if (!copy)
		{
			copy = malloc(sizeof(t_export));
			if (!copy)
				return (NULL);
			current = copy;
		}
		else
		{
			current->next = malloc(sizeof(t_export));
			if (!current->next)
				return (free_export(copy), NULL);
			current = current->next;
		}
		copy_export2(node, copy, current);
		node = node->next;
	}
	current->next = NULL;
	return (copy);
}

void	free_export(t_export *node)
{
	t_export	*current;

	while (node)
	{
		current = node;
		node = node->next;
		free(current->key);
		free(current->value);
		free(current);
	}
}

static t_export	*init_export(char *env)
{
	t_export	*node;
	char		*ptr;
	int			key_len;
	int			value_len;

	node = (t_export *)malloc(sizeof(t_export));
	ptr = strchr(env, '=');
	if (!node || !ptr)
		return (NULL);
	key_len = ptr - env;
	node->key = (char *)malloc(key_len + 1);
	if (!node->key)
		return (NULL);
	ft_strncpy(node->key, env, key_len);
	node->key[key_len] = '\0';
	value_len = ft_strlen(env) - key_len - 1;
	node->value = (char *)malloc(value_len + 1);
	if (!node->value)
		return (NULL);
	ft_strncpy(node->value, ptr + 1, value_len);
	node->value[value_len] = '\0';
	node->next = NULL;
	return (node);
}

t_export	*create_export_list(char **env)
{
	t_export	*list;
	t_export	*tail;
	t_export	*node;
	int			i;

	list = NULL;
	tail = NULL;
	i = 0;
	while (env[i])
	{
		node = init_export(env[i]);
		if (!node)
		{
			free_export(list);
			return (NULL);
		}
		if (!list)
			list = node;
		else
			tail->next = node;
		tail = node;
		i++;
	}
	return (list);
}
