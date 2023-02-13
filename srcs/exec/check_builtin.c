/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 23:16:32 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/12 17:13:42 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtins(char *str)
{
	if (!ft_strcmp(str, "exit"))
		return (1);
	else if (!ft_strcmp(str, "echo"))
		return (1);
	else if (!ft_strcmp(str, "cd"))
		return (1);
	else if (!ft_strcmp(str, "pwd"))
		return (1);
	else if (!ft_strcmp(str, "export"))
		return (1);
	else if (!ft_strcmp(str, "unset"))
		return (1);
	else if (!ft_strcmp(str, "env"))
		return (1);
	return (0);
}

int	execute_builtin(t_data *d, t_lst *l)
{
	if (!ft_strcmp(l->cmd, "echo"))
		cmd_echo(l);
	else if (!ft_strcmp(l->cmd, "cd"))
		cmd_cd(d, l);
	else if (!ft_strcmp(l->cmd, "pwd"))
		cmd_pwd();
	else if (!ft_strcmp(l->cmd, "export"))
		cmd_export(d, l);
	else if (!ft_strcmp(l->cmd, "unset"))
		return (0);
	else if (!ft_strcmp(l->cmd, "env"))
		cmd_env(d, l);
	else if (!ft_strcmp(l->cmd, "exit"))
		cmd_exit(d);
	return (0);
}
