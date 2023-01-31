/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenicho <mbenicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:19:46 by mbenicho          #+#    #+#             */
/*   Updated: 2023/01/31 19:19:46 by mbenicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(t_data *d, int code)
{
	rl_clear_history();
	ft_free_tab(d->env);
	ft_lst_free(d->l);
	free(d->tmp);
	exit(code);
}

int is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (!str[i])
		return (1);
	return (0);
}

int	prompt(t_data *d)
{
	char *str;

	str = NULL;
	d->tmp = NULL;
	while (1)
	{
		str = readline(COLOR PROMPT COLOR_RESET);
		if (!str)
			return (1);
		get_cmd(str, d->env);
		if (!d->tmp || (d->tmp && ft_strcmp(str, d->tmp) && !is_empty(str)))
			add_history(str);
		free(d->tmp);
		d->tmp = ft_strdup(str);
		if (!d->tmp)
			return (free(str), exit_shell(d, EXIT_FAILURE), 1);
	//	if (parse_line(d, str))
	//		return (exit_shell(d, EXIT_FAILURE), 1);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_data	d;

	(void)argv;
	if (argc != 1)
		return (write(2, "Error\n", 6), 1);
	d.env = init_env(env);
	if (!d.env)
		return (write(2, "Error\n", 6), 1);
	prompt(&d);
	return (0);
}
