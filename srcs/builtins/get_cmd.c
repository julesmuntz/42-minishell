/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 21:57:18 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/02 14:01:58 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_dots(char **env, t_builtins *data)
{
	if (!ft_strcmp(*data->cmd, ".") && !data->cmd[1])
		return (printf("bash: %s: filename argument required\n\
%s: usage: . filename [arguments]\n", *data->cmd, *data->cmd),
			ft_free_lines(data->cmd), exit(EXIT_SUCCESS), 0);
	else if (!ft_strcmp(*data->cmd, ".") && !chdir(data->cmd[1]))
		return (printf("bash: %s: %s: is a directory\n", *data->cmd,
				data->cmd[1]), ft_free_lines(data->cmd), exit(EXIT_SUCCESS), 0);
	else if (!ft_strcmp(*data->cmd, ".") && find_cmd(data->cmd[1], env, data))
		return (printf("bash: %s: %s: cannot execute binary file\n",
				*data->cmd, data->cmd_path),
			ft_free_lines(data->cmd), exit(EXIT_SUCCESS), 0);
	else if (!ft_strcmp(*data->cmd, ".") && chdir(data->cmd[1]))
		return (printf("bash: %s: %s: No such file or directory\n",
				*data->cmd, data->cmd[1]),
			ft_free_lines(data->cmd), exit(EXIT_SUCCESS), 0);
	else if (!ft_strcmp(*data->cmd, ".."))
		return (printf("%s: command not found\n", *data->cmd),
			ft_free_lines(data->cmd), exit(EXIT_SUCCESS), 0);
	return (0);
}

void	get_cmd(t_builtins *data, t_data *d)
{
	check_dots(d->env, data);
	if (valid_input(d->env, data) == FALSE)
		return ;
	else if (valid_input(d->env, data) == CUSTOM)
	{
		execute_builtin(d->env, data);
		return ;
	}
	else if (valid_input(d->env, data) == TRUE)
	{
		execve(data->cmd_path, data->cmd, d->env);
		return ;
	}
	ft_free_lines(data->cmd);
}
