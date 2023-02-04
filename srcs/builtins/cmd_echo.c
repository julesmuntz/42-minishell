/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 11:11:26 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/04 17:26:49 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_echo(t_builtins *data, t_data *d)
{
	int		i;
	int		c;

	i = 1;
	if (!data->cmd[1])
		printf("\n");
	else if (data->cmd[1])
	{
		while (data->cmd[i])
		{
			if ((ft_count_chars(data->cmd[i], '"') % 2 != 0)
				|| (ft_count_chars(data->cmd[i], '\'') % 2 != 0))
			{
				close(STDOUT_FILENO);
				ft_putstr_fd("> ", STDIN_FILENO);
				//le user devrait pouvoir ecrire
				return (0);
			}
			if (d->hide_quotes[i] == TRUE)
			{
				c = 0;
				while (data->cmd[i][c])
				{
					if ((data->cmd[i][c] == '\'') || (data->cmd[i][c] == '"'))
						c++;
					printf("%c", data->cmd[i][c]);
					c++;
				}
			}
			else
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
