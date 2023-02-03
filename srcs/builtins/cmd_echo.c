/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 11:11:26 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/03 17:53:54 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_echo(t_builtins *data, t_data *d)
{
	int	i;

	i = 1;
	(void)d;
	if (!data->cmd[1])
		printf("\n");
	else if (data->cmd[1])
	{
		while (data->cmd[i])
		{
			printf("%s", data->cmd[i]);
			if ((i + 1) == (int)ft_arrstrlen(data->cmd))
				break ;
			printf(" ");
			i++;
		}
		printf("\n");
	}
	return (0);
}
