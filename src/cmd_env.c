/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:21:43 by julmuntz          #+#    #+#             */
/*   Updated: 2023/01/29 18:49:02 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_env(t_builtins *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		if (i == (int)ft_arrstrlen(data->env) - 1)
			cmd_pwd();
		else
			printf("%s\n", data->env[i]);
		i++;
	}
	return (0);
}
