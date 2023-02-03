/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 21:57:18 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/03 18:23:07 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_cmd(char **cmd, t_data *d)
{
	t_builtins	data;

	data.cmd = cmd;
	if (valid_input(&data, d) == FALSE)
		return (1);
	else if (valid_input(&data, d) == CUSTOM)
		execute_builtin(&data, d);
	else if (valid_input(&data, d) == TRUE)
		execve(data.cmd_path, data.cmd, d->env);
	return (1);
}
