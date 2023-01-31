/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenicho <mbenicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:19:46 by mbenicho          #+#    #+#             */
/*   Updated: 2023/01/31 19:19:46 by mbenicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lst_add_back(t_lst **l, t_lst *new)
{
	t_lst	*tmp;

	tmp = *l;
	if (!*l)
		*l = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	ft_lst_free(t_lst *l)
{
	t_lst	*tmp;

	if (!l)
		return ;
	while (l)
	{
		tmp = l;
		l = l->next;
		free(tmp->cmd);
		ft_free_tab(tmp->arg);
		ft_free_redir(tmp->infile);
		ft_free_redir(tmp->outfile);
		free(tmp);
	}
}
