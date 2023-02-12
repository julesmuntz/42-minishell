/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:57:26 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/13 00:28:35 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_export(t_export *node)
{
	t_export	*current;
	t_export	*next;
	char		*swap;

	if (node == NULL)
		return ;
	current = node;
	while (current)
	{
		next = current->next;
		while (next)
		{
			if (ft_strcmp(current->key, next->key) > 0)
			{
				swap = current->key;
				current->key = next->key;
				next->key = swap;
				swap = current->value;
				current->value = next->value;
				next->value = swap;
			}
			next = next->next;
		}
		current = current->next;
	}
}

t_export	*free_export(t_export *node)
{
	t_export	*tmp;

	while (node)
	{
		tmp = node;
		node = node->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	return (NULL);
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
