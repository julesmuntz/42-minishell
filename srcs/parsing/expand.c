/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 22:18:46 by mbenicho          #+#    #+#             */
/*   Updated: 2023/02/05 22:55:27 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	replace_var2(t_data *d, t_tok *t)
{
	char	*str;
	int		i;

	i = 0;
	while (*t->str == '$' && d->env[i])
	{
		if (!ft_strncmp(d->env[i], t->str + 1, ft_strlen(t->str + 1)) \
		&& d->env[i][ft_strlen(t->str + 1)] == '=')
		{
			str = ft_strdup(d->env[i] + ft_strlen(t->str));
			if (!str)
				return (1);
			free(t->str);
			t->str = str;
			return (0);
		}
		i++;
	}
	str = ft_strdup("");
	if (!str)
		return (1);
	free(t->str);
	t->str = str;
	return (0);
}

static int	replace_var(t_data *d, t_tok *t)
{
	while (t)
	{
		if (*t->str == '$' && replace_var2(d, t))
			return (1);
		t = t->next;
	}
	return (0);
}

static int	isolate_var_name(char *str)
{
	int	i;

	if (*str != '$')
		return (0);
	i = 1;
	while (str[i] && str[i] != ' ' && str[i] != '$')
		i++;
	return (i);
}

static int	init_tok_list(t_tok **t, char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = isolate_var_name(str + i);
		if (j == 0)
		{
			while (str[i + j] && !(str[i + j] == '$' && \
			str[i + j + 1] != ' ' && str[i + j + 1] != 0))
			{
				if (str[i + j] == '\'')
					j += parse_quotes(str + i + j);
				j++;
			}
		}
		if (j && new_tok(t, str + i, j))
			return (free(str), free_tok(*t), 1);
		i += j;
	}
	return (0);
}

char	*expand_vars(t_data *d, char *str)
{
	char	*line;
	t_tok	*t;

	t = NULL;
	if (init_tok_list(&t, str))
		return (NULL);
	free(str);
	if (replace_var(d, t))
		return (free_tok(t), NULL);
	if (ft_tok_join(t, &line))
		return (free_tok(t), NULL);
	return (free_tok(t), line);
}
