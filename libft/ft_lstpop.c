/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:32:02 by julmuntz          #+#    #+#             */
/*   Updated: 2022/10/14 17:08:33 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lstpop(t_list **lst)
{
	t_list	*next_node;
	void	*retvalue;

	next_node = NULL;
	retvalue = NULL;
	if (*lst == NULL)
		return (NULL);
	next_node = (*lst)->next;
	retvalue = (*lst)->content;
	free(*lst);
	*lst = next_node;
	return (retvalue);
}
