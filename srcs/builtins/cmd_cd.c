/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 21:41:00 by julmuntz          #+#    #+#             */
/*   Updated: 2023/03/08 12:29:49 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_cd(t_lst *l)
{
	if (!ft_strcmp(l->arg[1], "~") || !l->arg[1])
	{
		g_exit_code = 0;
		chdir(getenv("HOME"));
		return (0);
	}
	if (l->arg[2])
	{
		g_exit_code = 1;
		ft_fprintf(STDERR_FILENO, "minishell: %s: too many arguments\n", l->cmd);
		return (0);
	}
	if (chdir(l->arg[1]))
	{
		g_exit_code = 1;
		ft_fprintf(STDERR_FILENO, "minishell: %s: %s\n", l->arg[1],
			strerror(errno));
		return (0);
	}
	g_exit_code = 0;
	return (0);
}
