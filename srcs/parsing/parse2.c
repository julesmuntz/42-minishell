/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:19:46 by mbenicho          #+#    #+#             */
/*   Updated: 2023/03/14 13:47:19 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parse_tok(t_tok **t, t_tok **redir, t_tok **arg)
{
	t_tok	*tmp;
	t_tok	*tmp2;

	while (*t)
	{
		tmp = *t;
		if (!ft_strcmp(tmp->str, "|") && !tmp->next)
			break ;
		if (!ft_strcmp(tmp->str, "|"))
			tmp = tmp->next;
		if (!ft_strncmp(tmp->str, ">", 1) || !ft_strncmp(tmp->str, "<", 1))
		{
			tmp2 = tmp->next;
			tok_extract(t, redir, tmp);
			tok_extract(t, redir, tmp2);
		}
		else
			tok_extract(t, arg, tmp);
	}
}

static int	init_cmd(t_data *d, t_tok *t)
{
	t_tok	*redir;
	t_tok	*arg;
	t_lst	*new;

	redir = NULL;
	arg = NULL;
	new = malloc(sizeof(*new));
	if (!new)
		return (free_tok(t), 1);
	new->cmd = NULL;
	new->redir = NULL;
	new->arg = NULL;
	new->next = NULL;
	parse_tok(&t, &redir, &arg);
	free_tok(t);
	if (init_arg(new, arg))
		return (free_tok(redir), free(new), 1);
	if (init_redir(&(new->redir), redir))
		return (ft_lst_free(new), 1);
	return (ft_lst_add_back(&d->l, new), 0);
}

int	init_list(t_data *d, t_tok *t)
{
	t_tok	*tmp;
	t_tok	*cmd;

	d->l = NULL;
	while (t)
	{
		cmd = t;
		while (t->next && ft_strcmp(t->next->str, "|"))
			t = t->next;
		tmp = t->next;
		t->next = NULL;
		t = tmp;
		if (init_cmd(d, cmd))
			return (free_tok(t), 1);
	}
	return (0);
}
