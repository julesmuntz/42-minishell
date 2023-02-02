/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:19:46 by mbenicho          #+#    #+#             */
/*   Updated: 2023/02/02 14:03:29 by julmuntz         ###   ########.fr       */
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

//fonction temporaire pour afficher les commandes apres parsing
void	ft_print_lst(t_lst *l)
{
	while (l)
	{
		printf("cmd = %s\n", l->cmd);
		printf("arg= ");
		print_tab(l->arg);
		printf("infile= ");
		print_redir(l->infile);
		printf("outfile= ");
		print_redir(l->outfile);
		printf("\n");
		l = l->next;
	}
}

int	prompt(t_data *d)
{
	pid_t		pid;
	t_builtins	data;
	t_tok		*t;
	char		*str;

	t = NULL;
	str = NULL;
	d->tmp = NULL;
	while (1)
	{
		str = readline(COLOR PROMPT COLOR_RESET);
		if (!str)
			return (exit_shell(d, EXIT_FAILURE), 1);
//////////////// boucle des commandes WIP ////////////
		pid = fork();
		if (pid == -1)
			return (1);
		if (pid == 0)
		{
			if (!ft_strcmp(str, "exit"))
				return (free(str), exit_shell(d, EXIT_SUCCESS), 0);
			if (ft_history(d, &str))
				return (exit_shell(d, EXIT_FAILURE), 1);
			if (parse_line(d, str, &data, t))
				return (exit_shell(d, EXIT_FAILURE), 1);
			get_cmd(&data, d);
			d->l = ft_lst_free(d->l);
			// str = readline(COLOR PROMPT COLOR_RESET);
			// if (!str)
			// 	return (exit_shell(d, EXIT_FAILURE), 1);
			return (0);
		}
//////////////////////////////////////////////////////
		// if (!ft_strcmp(str, "exit"))
		// 	return (free(str), exit_shell(d, EXIT_SUCCESS), 0);
		// if (ft_history(d, &str))
		// 	return (exit_shell(d, EXIT_FAILURE), 1);
		// if (parse_line(d, str, &data, t))
		// 	return (exit_shell(d, EXIT_FAILURE), 1);
		// // ft_print_lst(d->l);
		// d->l = ft_lst_free(d->l);
		// get_cmd(&data, d);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_data	d;

	(void)argv;
	d.l = NULL;
	if (argc != 1)
		return (write(2, "Error\n", 6), 1);
	d.env = init_env(env);
	if (!d.env)
		return (write(2, "Error\n", 6), 1);
	prompt(&d);
	return (0);
}
