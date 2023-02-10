/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:57:26 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/10 22:23:35 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	print_xprt(t_export *line)
// {
// 	while (line)
// 	{
		// split = ft_split(line->str, '=');
		// if (!split)
		// 	return ;
		// line->var->str = ft_strdup("TEST");
		// if (!line->var->str)
			// return ;
		// line->var->next->str = ft_strdup("!@#$");
		// if (!line->var->next->str)
			// return ;
		// line->var->next->next->str = ft_strdup("IYFXGDTYUI");
		// if (!line->var->next->next->str )
			// return ;
		// printf("declare -x %s\n", line->str);
		// ft_free_lines(split);
		// printf("declare -x %s\n", line->str );
		// printf("declare -x %s%s\"%s\"\n", line->var->str, line->var->next->str , line->var->next->next->str );
// 		line = line->next;
// 	}
// }

// static int	array_to_list(char **array, int size, t_export **ptr)
// {
// 	int	i;

// 	i = 0;
// 	while (i < size)
// 	{
// 		xprt_add_back(ptr, xprt_new(array[i]));
// 		i++;
// 	}
// 	if (!(*ptr)->next)
// 		return (ft_free_lines(array), xprt_clear(ptr), exit(EXIT_FAILURE), 0);
	// return (0);
// }

void	init_export(t_data *d)
{
// 	int			i;
// 	char		**copy;
// 	t_export	*line;
// 	t_export	*last;

// 	i = 0;
// 	copy = d->env;
// 	ft_sort_arrstr(copy, ft_arrstrlen(copy));
// 	array_to_list(copy, ft_arrstrlen(d->env), &line);
// 	last = xprt_last(line);
// 	sort_xprt(line);
// 	xprt_pop_last(&line);
// 	xprt_add_front(&line, last);
// 	xprt_pop(&line);
// 	print_xprt(line);
	return ;
}

	// while (line)
	// {
		// line->var = malloc(sizeof(char *) * ft_arrstrlen(d->env));
		// while (i < 4)
		// {
		// 	line->var[i] = malloc(sizeof(char) * 3);
		// 	i++;
		// }
	// 	if (ft_strchr(line->str, '='))
	// 		line->var = ft_split(line->str, '=');
	// 	else
	// 		line->var = ft_split(line->str, '\0');
	// 	line = line->next;
	// }

// head;
// head->key;
// head->value;
// head->next->key 

// {
// 	char *key;
// 	char *value;
// 	t_export *next;
// 	}