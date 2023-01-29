/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:21:43 by julmuntz          #+#    #+#             */
/*   Updated: 2023/01/29 21:31:59 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (i == (int)ft_arrstrlen(env) - 1)
		{
			printf("_=");
			cmd_pwd();
		}
		else
			printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
