/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 11:11:26 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/05 18:27:26 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_echo(t_builtins *data, t_data *d)
{
	int	i;

	i = 1;
	if (!data->cmd[1])
		printf("\n");
	else if (data->cmd[1])
	{
		while (data->cmd[i])
		{
			printf("%s", data->cmd[i]);
			if ((i) == (int)ft_arrstrlen(data->cmd) - 1)
				break ;
			printf(" ");
			i++;
		}
		printf("\n");
	}
	return (0);
}
