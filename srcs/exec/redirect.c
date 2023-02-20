/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:34:24 by mbenicho          #+#    #+#             */
/*   Updated: 2023/02/20 17:17:39 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	heredoc(t_data *d, char *limiter)
{
	char	*str;
	int 	fd;

	fd = open(".heredoc.tmp", O_WRONLY|O_CREAT|O_TRUNC, 00644);
	while (1)
	{
		str = readline("> ");
		if (!ft_strcmp(str, limiter))
			break ;
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
	}
	close(fd);
	d->in = open(".heredoc.tmp", O_RDONLY);
	return (0);
}

static int	open_infile(t_data *d, t_lst *l)
{
	int	i;

	i = 0;
	if (d->in != STDIN_FILENO)
		close(d->in);
	while (l->infile[i].str)
	{
		if (i)
			close(d->in);
		if (l->infile[i].type == 0)
			d->in = open(l->infile[i].str, O_RDONLY);
		else
			heredoc(d, l->infile[i].str);
		i++;
	}
	return (0);
}

static int	open_outfile(t_data *d, t_lst *l)
{
	int	i;

	i = 0;
	if (d->out != STDOUT_FILENO)
		close(d->out);
	while (l->outfile[i].str)
	{
		if (i)
			close(d->out);
		if (l->outfile[i].type == 0)
			d->out = open(l->outfile[i].str, O_WRONLY | O_CREAT| O_TRUNC, 00664);
		else
			d->out = open(l->outfile[i].str, O_WRONLY | O_CREAT| O_APPEND, 00664);
		i++;
	}
	return (0);
}

int	redirect(t_data *d, t_lst *l)
{
	if (l->infile)
		open_infile(d, l);
	if (l->outfile)
		open_outfile(d, l);
	return (0);
}
