/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:57:26 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/12 02:17:09 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_sprintf(char *line_export, char *key, char *value)
{
	int	key_len;
	int	value_len;
	int	cur;

	key_len = strlen(key);
	value_len = strlen(value);
	cur = 0;
	ft_strcpy(line_export, "declare -x ");
	cur = strlen(line_export);
	ft_strcpy(line_export + cur, key);
	cur += key_len;
	line_export[cur] = '=';
	cur++;
	line_export[cur] = '"';
	cur++;
	ft_strcpy(line_export + cur, value);
	cur += value_len;
	line_export[cur] = '"';
	cur++;
	line_export[cur] = '\0';
}

static t_export	*init_export(char *env)
{
	t_export	*node;
	char		*ptr;
	int			key_len;
	int			value_len;
	int			export_len;

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
	node->line_env = (char *)malloc(ft_strlen(env) + 1);
	if (!node->line_env)
		return (NULL);
	ft_strcpy(node->line_env, env);
	export_len = key_len + value_len + 16;
	node->line_export = (char *)malloc(export_len);
	if (!node->line_export)
		return (NULL);
	ft_sprintf(node->line_export, node->key, node->value);
	node->next = NULL;
	return (node);
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
		free(tmp->line_env);
		free(tmp->line_export);
		free(tmp);
	}
	return (NULL);
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
