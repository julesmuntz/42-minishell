/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:21:25 by julmuntz          #+#    #+#             */
/*   Updated: 2023/01/28 23:51:30 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int arc, char **arv, char **env)
{
	t_builtins	data;

	if (arc != 2 || !arv[1])
		return (printf("Please ENTER 1 command.\n"), exit(EXIT_SUCCESS), 0);
	data.env = env;
	data.cmd = ft_split(arv[1], ' ');
	if (valid_input(&data) == CUSTOM)
		execute_builtin(&data);
	else if (valid_input(&data) == TRUE)
		execute_builtin(&data);
	return (0);
}
