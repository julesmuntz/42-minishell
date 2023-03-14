/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:34:24 by mbenicho          #+#    #+#             */
/*   Updated: 2023/03/14 18:15:21 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	heredoc2(t_data *d)
{
	d->in = open(".heredoc.tmp", O_RDONLY);
	if (d->in == -1)
		return (ft_puterr("minishell: heredoc: failed to open\n"), \
		unlink(".heredoc.tmp"), 1);
	d->heredoc = 1;
	return (0);
}

static int	heredoc(t_data *d, char *limiter)
{
	char	*str;
	int		fd;

	fd = open(".heredoc.tmp", O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, 00777);
	if (fd == -1)
		return (ft_puterr("minishell: heredoc: failed to open\n"), 1);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &ctrl_c_heredoc);
		if (g_exit_code == -3)
		{
			g_exit_code = 130;
			break ;
		}
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
	close(fd);
	return (heredoc2(d));
}

static int	open_infile(t_data *d, char *str, int type)
{
	if (d->in != STDIN_FILENO)
		close(d->in);
	if (d->heredoc)
	{
		d->heredoc = 0;
		unlink(".heredoc.tmp");
	}
	if (type == 2)
		d->in = open(str, O_RDONLY);
	else if (heredoc(d, str))
		return (1);
	if (d->in == -1)
		return (ft_fprintf(STDERR_FILENO, "minishell: %s: %s\n", \
		str, strerror(errno)), 1);
	return (0);
}

static int	open_outfile(t_data *d, char *str, int type)
{
	if (d->out != STDOUT_FILENO)
		close(d->out);
	if (type == 0)
		d->out = open(str, \
		O_WRONLY | O_CREAT | O_TRUNC, 00664);
	else
		d->out = open(str, \
		O_WRONLY | O_CREAT | O_APPEND, 00664);
	if (d->out == -1)
		return (ft_fprintf(STDERR_FILENO, "minishell: %s: %s\n", \
		str, strerror(errno)), 1);
	return (0);
}

int	redirect(t_data *d, t_lst *l)
{
	int	i;

	i = 0;
	while (l->redir && l->redir[i].str)
	{
		if ((l->redir[i].type == 0 || l->redir[i].type == 1))
		{
			if (open_outfile(d, l->redir[i].str, l->redir[i].type))
				return (1);
		}
		else if (open_infile(d, l->redir[i].str, l->redir[i].type))
			return (1);
		i++;
	}
	return (0);
}
