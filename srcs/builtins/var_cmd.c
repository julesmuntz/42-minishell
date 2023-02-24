/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 18:54:10 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/24 19:31:22 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_export(t_export *current, t_data *d, t_lst *l)
{
	if (!l->arg[1])
	{
		current = d->x;
		while (current)
		{
			if (ft_strcmp(current->key, "_")
				&& ft_strcmp(current->value, getenv("_")))
			{
				if (current->key && !current->value)
					ft_fprintf(d->out, "declare -x %s\n", current->key);
				else if (current->key && current->value)
					ft_fprintf(d->out,
						"declare -x %s=\"%s\"\n", current->key, current->value);
			}
			current = current->next;
		}
		return (0);
	}
	return (0);
}

static int	print_env(t_export *current, t_data *d, t_lst *l)
{
	if (!l->arg[1])
	{
		current = d->x;
		while (current)
		{
			if (current->value)
				ft_fprintf(d->out,
					"%s=%s\n", current->key, current->value);
			current = current->next;
		}
		return (0);
	}
	ft_fprintf(STDERR_FILENO,
		"env: '%s': No such file or directory\n", l->arg[1]);
	return (0);
}

static int	unset_var(t_export *current, const char *key)
{
	t_export	*node;
	t_export	*previous;

	node = current;
	previous = NULL;
	if (!key)
		return (1);
	while (node != NULL)
	{
		if (!ft_strcmp(node->key, key))
		{
			if (previous == NULL)
				current = node->next;
			else
				previous->next = node->next;
			return (ft_strdel(&node->key), ft_strdel(&node->value),
				free(node), 0);
		}
		else
		{
			previous = node;
			node = node->next;
		}
	}
	return (0);
}

static int	var_cmd2(t_export *current, t_data *d, t_lst *l)
{
	if (!ft_strcmp(l->cmd, "unset") && unset_var(current, l->arg[1]))
		return (1);
	else if (!ft_strcmp(l->cmd, "export") && print_export(current, d, l))
		return (1);
	else if (!ft_strcmp(l->cmd, "env") && print_env(current, d, l))
		return (1);
	return (0);
}

int	var_cmd(t_data *d, t_lst *l)
{
	t_export	*current;
	int			plus;
	int			found;
	int			i;

	if (!ft_strcmp(l->cmd, "export") && l->arg[1])
	{
		i = 1;
		while (l->arg[i])
		{
			plus = 0;
			found = 0;
			current = d->x;
			if (get_var(d, l->arg[i], &plus))
				return (1);
			while (current)
			{
				if (!ft_strcmp(current->key, d->x->new_key) && d->x->new_key)
				{
					found = 1;
					update_var(current, d, l->arg[i], &plus);
					break ;
				}
				current = current->next;
			}
			create_var(current, d, found);
			i++;
		}
	}
	var_cmd2(current, d, l);
	return (0);
}

// int	cmd_export(t_data *d, t_lst *l)
// {
// 	t_export	*current;
// 	char		*value;
// 	char		*key;
// 	int			i;
// 	int			plus;
// 	int			found;
// 	char		*add;

// 	current = d->node;
// 	if (l->arg[1])
// 	{
// 		i = 0;
// 		plus = 0;
// 		while (l->arg[1][i] != '=' && l->arg[1][i])
// 		{
// 			if (l->arg[1][i] == '+')
// 				plus++;
// 			i++;
// 		}
// 		if (plus > 1)
// 		{
// 			printf("Error: more than one '+' found in variable declaration\n");
// 			return (0);
// 		}
// 		if (l->arg[1][i] == '=')
// 		{
// 			key = ft_strndup(l->arg[1], i - plus);
// 			value = ft_strndup(l->arg[1] + i + 1, ft_strlen(l->arg[1]) - i - 1);
// 		}
// 		else
// 		{
// 			key = ft_strdup(l->arg[1]);
// 			value = ft_strdup("");
// 		}
// 		found = 0;
// 		while (current)
// 		{
// 			if (!ft_strcmp(current->key, key))
// 			{
// 				found = 1;
// 				if (plus == 1)
// 				{
// 					add = ft_strjoin(current->value, value);
// 					ft_strdel(&current->value);
// 					current->value = add;
// 				}
// 				else if (ft_strcmp(value, "") && ft_strcmp(current->value,
// 							value))
// 				{
// 					ft_strdel(&current->value);
// 					current->value = value;
// 				}
// 				else if (!ft_strcmp(current->value, ""))
// 				{
// 					ft_strdel(&current->value);
// 					current->value = value;
// 				}
// 				break ;
// 			}
// 			current = current->next;
// 		}
// 		if (!found)
// 		{
// 			current = d->node;
// 			while (current->next)
// 				current = current->next;
// 			current->next = (t_export *)malloc(sizeof(t_export));
// 			current->next->key = key;
// 			current->next->value = value;
// 			current->next->next = NULL;
// 		}
// 	}
// 	sort_export(d->node);
// 	current = d->node;
// 	if (!l->arg[1])
// 	{
// 		while (current != NULL)
// 		{
// 			if (!ft_strcmp(current->value, ""))
// 				printf("declare -x %s\n", current->key);
// 			else
// 				printf("declare -x %s=\"%s\"\n", current->key, current->value);
// 			current = current->next;
// 		}
// 	}
// 	return (0);
// }