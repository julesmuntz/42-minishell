/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:19:46 by mbenicho          #+#    #+#             */
/*   Updated: 2023/03/07 15:02:39 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(t_data *d, int code)
{
	rl_clear_history();
	free(d->prompt);
	ft_lst_free(d->l);
	free(d->tmp);
	free_garbage(&d->g);
	exit(code);
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
	char		*str;

	str = NULL;
	d->tmp = NULL;
	d->prompt = NULL;
	rl_outstream = stderr;//tmp
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_ctrl_c);
		if (refresh_prompt(d))
			return (exit_shell(d, EXIT_FAILURE));
		str = readline(d->prompt);
		if (!str)
		{
			ft_puterr("exit\n");
			return (exit_shell(d, EXIT_FAILURE));
		}
		if (ft_history(d, &str) || parsing(d, str) || exe_cmd(d))
			return (exit_shell(d, EXIT_FAILURE));
		free(d->prompt);
		d->l = ft_lst_free(d->l);
	}
}

int	g_exit_code = 0;

int	main(int argc, char **argv, char **env)
{
	t_data	d;

	(void)argv;
	d.l = NULL;
	d.g = NULL;
	if (argc != 1)
		return (ft_puterr("Error\n"), 1);
	d.env = init_env(env, &d);
	if (!d.env)
		return (ft_puterr("Error\n"), 1);
	d.x = init_export(&d);
	if (!d.x)
		return (ft_puterr("Error\n"), 1);
	prompt(&d);
	return (0);
}
