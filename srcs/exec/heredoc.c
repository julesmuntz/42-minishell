/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 21:20:52 by mbenicho          #+#    #+#             */
/*   Updated: 2023/03/15 01:13:32 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	event(void)
{
	return (0);
}

static void	ctrl_c(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_code = -3;
		rl_replace_line("", 0);
		rl_done = 1;
	}
}

static int	heredoc_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrl_c);
	if (g_exit_code == -3)
	{
		g_exit_code = 130;
		return (1);
	}
	rl_event_hook = event;
	return (0);
}

static int	heredoc2(t_data *d, char *limiter, int fd)
{
	char	*str;

	while (1)
	{
		if (heredoc_signal())
			return (1);
		str = readline("> ");
		if (!str)
		{
			ft_fprintf(STDERR_FILENO, "minishell: warning: here-document \
at line %d delimited by end-of-file (wanted '%s')\n", d->heredoc_line, limiter);
			break ;
		}
		if (!ft_strcmp(str, limiter))
			break ;
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
		d->heredoc_line++;
	}
	return (0);
}

int	heredoc(t_data *d, char *limiter)
{
	int		fd;

	fd = open(".heredoc.tmp", O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, 00777);
	if (fd == -1)
		return (ft_puterr("minishell: heredoc: failed to open\n"), 1);
	if (heredoc2(d, limiter, fd))
		return (close(fd), unlink(".heredoc.tmp"), 1);
	close(fd);
	d->in = open(".heredoc.tmp", O_RDONLY);
	if (d->in == -1)
		return (ft_puterr("minishell: heredoc: failed to open\n"), \
		unlink(".heredoc.tmp"), 1);
	d->heredoc = 1;
	return (0);
}
