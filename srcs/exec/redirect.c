/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:34:24 by mbenicho          #+#    #+#             */
/*   Updated: 2023/03/14 21:27:51 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (g_exit_code = 130, 1);
	if (d->in == -1)
		return (ft_fprintf(STDERR_FILENO, "minishell: %s: %s\n", \
		str, strerror(errno)), g_exit_code = 1, 1);
	return (g_exit_code = 0, 0);
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
		str, strerror(errno)), g_exit_code = 1, 1);
	return (g_exit_code = 0, 0);
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
