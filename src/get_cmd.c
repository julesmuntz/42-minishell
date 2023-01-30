/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 21:57:18 by julmuntz          #+#    #+#             */
/*   Updated: 2023/01/30 12:23:38 by julmuntz         ###   ########.fr       */
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

int	get_cmd(int arc, char **arv, char **env)
{
	t_builtins	data;
	int			i;

	i = -1;
	if (arc != 2 || !arv[1])
		return (printf("Please ENTER 1 command.\n"), exit(EXIT_SUCCESS), 0);
	while (arv[1][++i])
		if (!ft_isspace(arv[1][i]))
			break ;
	if (!arv[1][i])
		return (0);
	data.cmd = ft_split(arv[1], ' ');
	check_dots(env, &data);
	if (valid_input(env, &data) == FALSE)
		return (0);
	else if (valid_input(env, &data) == CUSTOM)
		execute_builtin(env, &data);
	else if (valid_input(env, &data) == TRUE)
		execute_builtin(env, &data);
	ft_free_lines(data.cmd);
	return (0);
}
