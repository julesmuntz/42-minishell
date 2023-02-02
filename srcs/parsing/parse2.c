/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenicho <mbenicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:19:46 by mbenicho          #+#    #+#             */
/*   Updated: 2023/01/31 19:19:46 by mbenicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_tok(t_tok **t, t_tok **infile, t_tok **outfile, t_tok **arg)
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
		if (!ft_strncmp(tmp->str, ">", 1))
		{
			tmp2 = tmp->next;
			tok_extract(t, outfile, tmp);
			tok_extract(t, outfile, tmp2);
		}
		else if (!ft_strncmp(tmp->str, "<", 1))
		{
			tmp2 = tmp->next;
			tok_extract(t, infile, tmp);
			tok_extract(t, infile, tmp2);
		}
		else
			tok_extract(t, arg, tmp);
	}
}

int	init_outfile(t_lst **new, t_tok *t)
{
	int		size;
	int		i;
	t_tok	*tmp;

	if (t)
	{
		size = ft_tok_size(t) / 2;
		(*new)->outfile = malloc((size + 1) * sizeof(t_redir));
		if (!(*new)->infile)
			return (free_tok(t), 1);
		(*new)->outfile[size].str = NULL;
		i = 0;
		tmp = t;
		while (tmp)
		{
			(*new)->outfile[i].type = 0;
			if (!ft_strcmp(tmp->str, "<<"))
				(*new)->outfile[i].type = 1;
			tmp = tmp->next;
			(*new)->outfile[i].str = ft_strdup(tmp->str);
			if (!(*new)->outfile[i].str)
				return (free_tok(t), ft_free_redir((*new)->outfile), 1);
			tmp = tmp->next;
			i++;
		}
	}
	return (free_tok(t), 0);
}


int	init_infile(t_lst **new, t_tok *t)
{
	int		size;
	int		i;
	t_tok	*tmp;

	if (t)
	{
		size = ft_tok_size(t) / 2;
		(*new)->infile = malloc((size + 1) * sizeof(t_redir));
		if (!(*new)->infile)
			return (free_tok(t), 1);
		(*new)->infile[size].str = NULL;
		i = 0;
		tmp = t;
		while (tmp)
		{
			(*new)->infile[i].type = 0;
			if (!ft_strcmp(tmp->str, "<<"))
				(*new)->infile[i].type = 1;
			tmp = tmp->next;
			(*new)->infile[i].str = ft_strdup(tmp->str);
			if (!(*new)->infile[i].str)
				return (free_tok(t), ft_free_redir((*new)->infile), 1);
			tmp = tmp->next;
			i++;
		}
	}
	return (free_tok(t), 0);
}

int	init_cmd(t_data *d, t_tok *t)
{
	t_tok	*infile;
	t_tok	*outfile;
	t_tok	*arg;
	t_lst	*new;

	infile = NULL;
	outfile = NULL;
	arg = NULL;
	new = malloc(sizeof(*new));
	if (!new)
		return (free_tok(t), 1);
	new->cmd = NULL;
	new->infile = NULL;
	new->outfile = NULL;
	new->arg = NULL;
	new->next = NULL;
	parse_tok(&t, &infile, &outfile, &arg);
	free_tok(t);

	//print_tok(infile);
	//print_tok(outfile);
	//print_tok(arg);
	//printf("\n");

	if (init_arg(new, arg))
		return (free_tok(infile), free_tok(outfile), free(new), 1);
//	if (init_infile(&new, infile))
//		return (free_tok(outfile), ft_lst_free(new), 1);
//	if (init_outfile(&new, outfile))
//		return (ft_lstfree(new), 1);
	
	free_tok(infile);
	free_tok(outfile);
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
		//free_tok(cmd);
	}
	return (0);
}
