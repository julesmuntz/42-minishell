/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenicho <mbenicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:19:46 by mbenicho          #+#    #+#             */
/*   Updated: 2023/01/31 19:19:46 by mbenicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tok(t_tok *t)
{
	while (t)
	{
		printf("'%s'\n", t->str);
		t = t->next;
	}
}

int	syntax_check(t_tok *t)
{
	if (!ft_strcmp(t->str, "|"))
		return (1);
	while (t)
	{
		if ((!ft_strncmp(t->str, "<", 1) || \
		!ft_strncmp(t->str, ">", 1) || !ft_strcmp(t->str, "|")) && \
		(!t->next || (!ft_strncmp(t->next->str, "<", 1) || \
		!ft_strncmp(t->next->str, ">", 1) || \
		!ft_strcmp(t->next->str, "|"))))
			return (1);
		t = t->next;
	}
	return (0);
}

int	is_meta(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

int	parse_line(t_data *d, char *str)
{
	int		i;
	int		j;
	t_tok	*t;

	t = NULL;
	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i] == ' ')
			i++;
		if (is_meta(str[i]))
		{
			j = 1;
			if ((str[i] == '>' && str[i + 1] == '>') \
			|| (str[i] == '<' && str[i + 1] == '<'))
				j = 2;
		} 
		else
		{
			while (str[i + j] && str[i + j] != ' ' && !is_meta(str[i + j]))
				j++;
		}
		if (j && new_tok(&t, str + i, j))
			return (free(str), free_tok(t), write(2, "Error\n", 6), 1);
		i += j;
	}
	free(str);
	//print_tok(t);
	if (syntax_check(t))
		return (free_tok(t), write(2, "Syntax error\n", 13), 1);
	if (init_list(d, t))
		return (write(2, "Error\n", 6), 1);
	return (0);
}
