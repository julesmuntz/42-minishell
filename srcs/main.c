/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:19:46 by mbenicho          #+#    #+#             */
/*   Updated: 2023/02/09 13:11:52 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(t_data *d, int code)
{
	rl_clear_history();
	free(d->prompt);
	ft_free_tab(d->env);
	ft_lst_free(d->l);
	free(d->tmp);
	exit(code);
}

// fonction temporaire pour afficher les commandes apres parsing
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

int	ft_history(t_data *d, char **str)
{
	char	*s;

	s = ft_strtrim(*str, " ");
	free(*str);
	if (!s)
		return (1);
	*str = s;
	if (!d->tmp || (d->tmp && ft_strcmp(s, d->tmp) && s[0]))
		add_history(s);
	free(d->tmp);
	d->tmp = ft_strdup(s);
	if (!d->tmp)
		return (free(s), 1);
	return (0);
}

void	prompt(t_data *d)
{
	char	*str;

	str = NULL;
	d->tmp = NULL;
	while (1)
	{
		signal(SIGINT, &handle_signals);
		signal(SIGQUIT, SIG_IGN);
		if (refresh_prompt(d))
			return (exit_shell(d, EXIT_FAILURE));
		str = readline(d->prompt);
		if (!str)
			return (exit_shell(d, EXIT_FAILURE));
		if (ft_history(d, &str))
			return (exit_shell(d, EXIT_FAILURE));
		if (parsing(d, str))
			return (exit_shell(d, EXIT_FAILURE));
		if (exe_cmd(d))
			return (exit_shell(d, EXIT_FAILURE));
		d->l = ft_lst_free(d->l);
	}
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
