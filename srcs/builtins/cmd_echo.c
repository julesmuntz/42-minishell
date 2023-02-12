/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 11:11:26 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/06 11:58:06 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_echo(t_lst *l)
{
	int	i;

	i = 1;
	if (!ft_strcmp(l->arg[1], "-n"))
		i = 2;
	if (!l->arg[1])
		printf("\n");
	else if (l->arg[1])
	{
		while (l->arg[i])
		{
			printf("%s", l->arg[i]);
			if ((i) == (int)ft_arrstrlen(l->arg) - 1)
				break ;
			printf(" ");
			i++;
		}
		if (ft_strcmp(l->arg[1], "-n"))
			printf("\n");
	}
}
