/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 23:16:32 by julmuntz          #+#    #+#             */
/*   Updated: 2023/03/13 16:30:59 by julmuntz         ###   ########.fr       */
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
	if (!ft_strcmp(l->cmd, "echo") && cmd_echo(d, l))
		return (1);
	else if (!ft_strcmp(l->cmd, "cd") && cmd_cd(d, l))
		return (1);
	else if (!ft_strcmp(l->cmd, "pwd") && cmd_pwd(d))
		return (1);
	else if (!ft_strcmp(l->cmd, "export") && var_cmd(d, l))
		return (1);
	else if (!ft_strcmp(l->cmd, "unset") && var_cmd(d, l))
		return (1);
	else if (!ft_strcmp(l->cmd, "env") && var_cmd(d, l))
		return (1);
	else if (!ft_strcmp(l->cmd, "exit") && cmd_exit(d, l))
		return (1);
	if (d->in != STDIN_FILENO)
		close(d->in);
	if (d->out != STDOUT_FILENO)
		close(d->out);
	return (0);
}
