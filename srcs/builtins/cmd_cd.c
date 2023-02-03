/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 21:41:00 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/03 18:18:48 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_cd(t_builtins *data, t_data *d)
{
	char	*path;

	path = find_cmd(data->cmd[1], d->env, data);
	if (!path)
	{
		printf("bash: %s: %s: No such file or directory\n",
			data->cmd[0], data->cmd[1]);
		return (0);
	}
	chdir(path);
	return (0);
}
