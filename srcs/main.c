/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:19:46 by mbenicho          #+#    #+#             */
/*   Updated: 2023/03/16 13:13:06 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(t_data *d, int code)
{
	rl_clear_history();
	ft_lst_free(d->l);
	free(d->tmp);
	free_garbage(&d->g);
	exit(code);
}

static void	ctrl_c(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_code = 130;
	}
}

static int	ft_history(t_data *d, char **str)
{
	char	*s;

	s = ft_strtrim(*str, " \t\n");
	free(*str);
	if (!s)
		return (ft_puterr("minishell: malloc failed\n"), 1);
	*str = s;
	if (!d->tmp || (d->tmp && ft_strcmp(s, d->tmp) && s[0]))
		add_history(s);
	free(d->tmp);
	d->tmp = ft_strdup(s);
	if (!d->tmp)
		return (ft_puterr("minishell: malloc failed\n"), free(s), 1);
	return (0);
}

void	prompt(t_data *d)
{
	char		*str;

	str = NULL;
	d->tmp = NULL;
	d->prompt = NULL;
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &ctrl_c);
		if (refresh_prompt(d))
			return (exit_shell(d, EXIT_FAILURE));
		str = readline(d->prompt);
		if (!str)
		{
			ft_puterr("exit\n");
			return (exit_shell(d, g_exit_code));
		}
		if (ft_history(d, &str) || parsing(d, str) || exe_cmd(d))
			return (exit_shell(d, EXIT_FAILURE));
		d->env = update_env(d);
		d->l = ft_lst_free(d->l);
	}
}

int	g_exit_code = 0;

int	main(int argc, char **argv, char **env)
{
	t_data	d;
	char	buf[4096];

	(void)argv;
	d.l = NULL;
	d.g = NULL;
	d.main = 1;
	d.heredoc_line = 0;
	if (argc != 1)
		return (ft_puterr("minishell: too many arguments\n"), 1);
	if (!isatty(0))
		return (ft_puterr("minishell: stdin is not a tty\n"), 1);
	d.user = getenv("USER");
	if (!d.user)
		d.user = "user";
	d.env = init_env(env, &d);
	if (!d.env)
		return (ft_puterr("minishell: malloc failed\n"), 1);
	d.x = init_export(&d);
	if (!d.x)
		return (ft_puterr("minishell: malloc failed\n"), 1);
	ft_setenv("PWD", getcwd(buf, sizeof(buf)), &d);
	prompt(&d);
	return (0);
}
