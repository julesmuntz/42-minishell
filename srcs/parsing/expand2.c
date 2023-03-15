/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:43:47 by mbenicho          #+#    #+#             */
/*   Updated: 2023/03/13 15:44:07 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	separate_quotes(t_tok **t, char *s)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
	{
		j = parse_quotes(s + i);
		if (j)
			j++;
		if (j == 0)
		{
			while (s[i + j])
			{
				if (is_quotes(s, i, j))
					break ;
				j++;
			}
			if (j && new_tok(t, s + i, j))
				return (free_tok(*t), 1);
		}
		else if (j && new_tok(t, s + i, j))
			return (free_tok(*t), 1);
		i += j;
	}
	return (0);
}

static int	isolate_var_name(char *str)
{
	int	i;

	i = 0;
	if (*str != '$')
		return (0);
	if (*(str + 1) == '?')
		return (2);
	i = 1;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	return (i);
}

int	init_tok_list(t_tok **t, char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		if (str[i] == '\'' || str[i] == '"')
			j = parse_quotes_expand(str + i);
		if (j == 0)
			j = isolate_var_name(str + i);
		else
			j++;
		if (j == 0)
		{
			while (str[i + j] && str[i + j] != '$')
				j++;
		}
		if (j && new_tok(t, str + i, j))
			return (free(str), free_tok(*t), 1);
		i += j;
	}
	return (0);
}

int	parse_quotes_expand(char *str)
{
	int	i;
	int	j;

	i = 1;
	if (str[0] == '"')
		while (str[i] && str[i] != '"')
			i++;
	else if (str[0] == '\'')
		while (str[i] && str[i] != '\'')
			i++;
	else
		return (0);
	if (str[i] == 0)
		i = 0;
	else if (str[i] == '"')
	{
		j = i - 1;
		while (j > 0 && str[j] == '\'')
			j--;
		if (str[j] != '$')
			i = 0;
	}
	return (i);
}
