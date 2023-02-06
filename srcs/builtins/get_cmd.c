/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 21:57:18 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/06 12:45:57 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check(char **env, t_builtins *data)
{
	if (!chdir(data->cmd[0]))
		return (printf("bash: %s: is a directory\n", data->cmd[0]), 0);
	else if (!ft_strcmp(data->cmd[0], ".") && !data->cmd[1])
		return (printf("bash: %s: filename argument required\n\
%s: usage: . filename [arguments]\n", data->cmd[0], data->cmd[0]), 0);
	else if (!ft_strcmp(data->cmd[0], ".") && !chdir(data->cmd[1]))
		return (printf("bash: %s: %s: is a directory\n", data->cmd[0],
				data->cmd[1]), 0);
	else if (!ft_strcmp(data->cmd[0], ".") && find_cmd(data->cmd[1], env, data))
		return (printf("bash: %s: %s: cannot execute binary file\n",
				data->cmd[0], data->cmd_path), 0);
	else if (!ft_strcmp(data->cmd[0], ".") && chdir(data->cmd[1]))
		return (printf("bash: %s: %s: No such file or directory\n",
				data->cmd[0], data->cmd[1]), 0);
	else if (!ft_strcmp(data->cmd[0], ".."))
		return (printf("%s: command not found\n", data->cmd[0]), 0);
	return (0);
}

int	get_cmd(char **cmd, t_data *d)
{
	t_builtins	data;

	data.cmd = cmd;
	check(d->env, &data);
	if (valid_input(&data, d) == FALSE)
		return (1);
	else if (valid_input(&data, d) == CUSTOM)
		execute_builtin(&data, d);
	return (1);
}
