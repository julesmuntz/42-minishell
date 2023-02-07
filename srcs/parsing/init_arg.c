/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 22:18:46 by mbenicho          #+#    #+#             */
/*   Updated: 2023/02/07 20:09:47 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	remove_path(char **str)
{
	int		i;
	char	*tmp;

	i = ft_strlen(*str);
	while (i > 0 && (*str)[i - 1] != '/')
		i--;
	if (ft_strlen(*str) > 0)
	{
		tmp = ft_strdup(*str + i);
		if (!tmp)
			return (1);
		free(*str);
		*str = tmp;
	}
	return (0);
}

static int	init_arg2_path(t_lst *new, t_tok *t, int size)
{
	int		i;
	char	*str;
	t_tok	*tmp;

	i = 0;
	tmp = t;
	str = NULL;
	while (i < size)
	{
		if (remove_quotes(tmp->str, &str))
			return (1);
		new->arg_path[i] = ft_strdup(str);
		free(str);
		if (!new->arg_path[i])
			return (1);
		tmp = tmp->next;
		i++;
	}
	new->arg_path[i] = NULL;
	return (0);
}

static int	init_arg2(t_lst *new, t_tok *t, int size)
{
	int		i;
	char	*str;
	t_tok	*tmp;

	i = 0;
	tmp = t;
	str = NULL;
	while (i < size)
	{
		if (remove_quotes(tmp->str, &str))
			return (1);
		if (remove_path(&str))
			return (1);
		new->arg[i] = ft_strdup(str);
		free(str);
		if (!new->arg[i])
			return (1);
		tmp = tmp->next;
		i++;
	}
	new->arg[i] = NULL;
	return (0);
}

int	init_arg(t_lst *new, t_tok *t)
{
	int		size;

	if (t)
	{
		new->cmd = ft_strdup(t->str);
		if (!new->cmd)
			return (free_tok(t), 1);
		size = ft_tok_size(t);
		new->arg = malloc((size + 1) * sizeof(char *));
		if (!new->arg)
			return (free(new->cmd), free_tok(t), 1);
		if (init_arg2(new, t, size))
			return (free(new->cmd), free_tok(t), \
			ft_free_tab((new->arg)), 1);
		new->arg_path = malloc((size + 1) * sizeof(char *));
		if (!new->arg_path)
			return (free(new->cmd), free_tok(t), 1);
		if (init_arg2_path(new, t, size))
			return (free(new->cmd), free_tok(t), \
			ft_free_tab((new->arg)), ft_free_tab((new->arg_path)), 1);
	}
	return (free_tok(t), 0);
}
