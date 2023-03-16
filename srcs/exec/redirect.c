/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:34:24 by mbenicho          #+#    #+#             */
/*   Updated: 2023/03/16 13:14:39 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_files(t_data *d)
{
	t_lst	*lst;
	int		i;
	int		fd;
	t_redir	*r;

	lst = d->l;
	while (lst)
	{
		i = 0;
		r = lst->redir;
		while (r && r[i].str)
		{
			if ((r[i].type == 0 || r[i].type == 1) && access(r[i].str, F_OK))
			{
				fd = open(r[i].str, O_CREAT, 00664);
				close(fd);
			}
			i++;
		}
		lst = lst->next;
	}
}

static int	open_infile(t_data *d, char *str, int type)
{
	if (!ft_strcmp(str, "/dev/stdin"))
		return (0);
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
	if (!ft_strcmp(str, "/dev/stdout"))
		return (0);
	if (d->out != STDOUT_FILENO)
		close(d->out);
	if (type == 0)
		d->out = open(str, \
		O_WRONLY | O_TRUNC);
	else
		d->out = open(str, \
		O_WRONLY | O_APPEND);
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
