/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 18:54:10 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/13 20:20:02 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_vars(t_export *current, t_data *d, t_lst *l)
{
	sort_export(d->x);
	current = d->x;
	if (!l->arg[1])
	{
		while (current != NULL)
		{
			if (!ft_strcmp(current->value, ""))
				ft_fprintf(STDOUT_FILENO, "declare -x %s\n", current->key);
			else
				ft_fprintf(STDOUT_FILENO,
					"declare -x %s=\"%s\"\n", current->key, current->value);
			current = current->next;
		}
	}
}

static void	create_var(t_export *current, t_data *d, int found)
{
	current = d->x;
	if (!found)
	{
		while (current->next)
			current = current->next;
		current->next = (t_export *)malloc(sizeof(t_export));
		current->next->key = d->x->new_key;
		current->next->value = d->x->new_value;
		current->next->next = NULL;
	}
}

static void	update_var(t_export *current, char *new, int *plus, int *found)
{
	char	*add;

	*found = 1;
	if (*plus == 1)
	{
		add = ft_strjoin(current->value, new);
		ft_strdel(&current->value);
		current->value = add;
	}
	else if (ft_strcmp(new, "") && ft_strcmp(current->value, new))
	{
		ft_strdel(&current->value);
		current->value = new;
	}
	else if (!ft_strcmp(current->value, ""))
	{
		ft_strdel(&current->value);
		current->value = new;
	}
}

static int	get_var(t_data *d, t_lst *l, int *plus)
{
	int	i;

	i = 0;
	while (l->arg[1][i] != '=' && l->arg[1][i])
	{
		if (l->arg[1][i] == '+')
			(*plus)++;
		i++;
	}
	if (*plus > 1)
		return (ft_fprintf(STDERR_FILENO,
				"bash: export: `%s\': not a valid identifier\n", l->arg[1]), 1);
	if (l->arg[1][i] == '=')
	{
		d->x->new_key = ft_strndup(l->arg[1], i - *plus);
		d->x->new_value = ft_strndup(l->arg[1] + i + 1,
				ft_strlen(l->arg[1]) - i - 1);
	}
	else
	{
		d->x->new_key = ft_strdup(l->arg[1]);
		d->x->new_value = ft_strdup("");
	}
	return (0);
}

int	cmd_export(t_data *d, t_lst *l)
{
	t_export	*current;
	int			plus;
	int			found;

	plus = 0;
	found = 0;
	current = d->x;
	if (l->arg[1])
	{
		if (get_var(d, l, &plus))
			return (1);
		while (current)
		{
			if (!ft_strcmp(current->key, d->x->new_key))
			{
				update_var(current, d->x->new_value, &plus, &found);
				break ;
			}
			current = current->next;
		}
		create_var(current, d, found);
	}
	print_vars(current, d, l);
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