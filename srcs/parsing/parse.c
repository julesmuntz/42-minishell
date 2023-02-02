/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:19:46 by mbenicho          #+#    #+#             */
/*   Updated: 2023/02/02 20:02:39 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tok(t_tok *t)
{
	while (t)
	{
		printf("'%s' ", t->str);
		t = t->next;
	}
	printf("\n");
}

int	syntax_check(t_tok *t)
{
	if (!ft_strcmp(t->str, "|"))
		return (1);
	while (t)
	{
		if (((*(t->str) == '>' || *(t->str) == '<') && (!t->next \
		|| *(t->next->str) == '>' || *(t->next->str) == '<' || \
		*(t->next->str) == '|')) || (*(t->str) == '|' && !t->next))
			return (1);
		t = t->next;
	}
	return (0);
}

int	is_meta(char *str)
{
	int	i;

	i = 0;
	if (*str == '|' || *str == '>' || *str == '<')
	{
		i = 1;
		if ((*str == '>' && *(str + 1) == '>') \
		|| (*str == '<' && *(str + 1) == '<'))
			i = 2;
	}
	return (i);
}

int	parse_quotes(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '"')
		while (str[i] && str[i] != '"')
			i++;
	else
		while (str[i] && str[i] != '\'')
			i++;
	if (!str[i])
		i = 0;
	return (i);
}

int	parse_line(t_data *d, char *str, t_builtins *data, t_tok *t)
{
	int		i;
	int		j;

	i = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		j = is_meta(str + i);
		if (j == 0)
		{
			while (str[i + j] && str[i + j] != ' ' && !is_meta(str + i + j))
			{
				if (str[i + j] == '"' || str[i + j] == '\'')
					j += parse_quotes(str + i + j);
				j++;
			}
		}
		if (j && new_tok(&t, str + i, j))
			return (free(str), free_tok(t), write(2, "Unexpected error\n", 17), 1);
		i += j;
	}
	data->cmd = malloc(sizeof(char *) * ft_tok_size(t));
	token_to_array(t, data->cmd);
	// if (syntax_check(t))
	// 	return (free_tok(t), write(2, "Syntax error\n", 13), 1);
	// if (init_list(d, t))
	// 	return (write(2, "Unexpected error\n", 17), 1);
//	print_tok(t);
	(void)d;
	return (0);
}
