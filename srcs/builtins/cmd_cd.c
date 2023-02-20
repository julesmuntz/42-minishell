/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 21:41:00 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/20 19:30:57 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_cd(t_lst *l)
{
	if (!ft_strcmp(l->arg[1], "~") || !l->arg[1])
	{
		chdir(getenv("HOME"));
		return (0);
	}
	else if (!l->arg[1])
		return (0);
	if (l->arg[2])
	{
		ft_fprintf(STDERR_FILENO, "minishell: %s: too many arguments\n", l->cmd);
		return (0);
	}
	if (chdir(l->arg[1]))
		ft_fprintf(STDERR_FILENO, "minishell: %s: %s\n", l->arg[1],
			strerror(errno));
	return (0);
}
