/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 21:41:00 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/02 20:02:17 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_cd(char **env, t_builtins *data)
{
	char *path;

	path = find_cmd(data->cmd[1], env, data);
	// if (data->cmd[1] && data->cmd[2])
	// {

	// }
	// else if (data->cmd[1] && !data->cmd[2])
	// {
		if (!path)
		{
			return (0);
		}
		chdir(path);
	// }
	return (0);
}
