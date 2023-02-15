/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:19:46 by mbenicho          #+#    #+#             */
/*   Updated: 2023/02/15 02:25:46 by julmuntz         ###   ########.fr       */
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

t_lst	*ft_lst_free(t_lst *l)
{
	t_lst	*tmp;

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
	return (NULL);
}
