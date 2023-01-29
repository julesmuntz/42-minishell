/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 21:57:18 by julmuntz          #+#    #+#             */
/*   Updated: 2023/01/29 22:33:56 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_cmd(int arc, char **arv, char **env)
{
	t_builtins	data;
	int			i;

	i = 0;
	if (arc != 2 || !arv[1])
		return (printf("Please ENTER 1 command.\n"), exit(EXIT_SUCCESS), 0);
	while (arv[1][i])
	{
		if (!ft_isspace(arv[1][i]))
			break ;
		i++;
	}
	if (!arv[1][i])
		return (0);
	data.cmd = ft_split(arv[1], ' ');
	if (valid_input(env, &data) == FALSE)
		return (0);
	else if (valid_input(env, &data) == CUSTOM)
		execute_builtin(env, &data);
	else if (valid_input(env, &data) == TRUE)
		execute_builtin(env, &data);
	ft_free_lines(data.cmd);
	return (0);
}
