/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 18:43:50 by mbenicho          #+#    #+#             */
/*   Updated: 2023/03/08 16:13:43 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	dup_fds(t_data *d)
{
	int	error;

	error = 0;
	if (d->in != STDIN_FILENO)
	{
		close(0);
		error = dup2(d->in, 0);
		close(d->in);
	}
	if (d->out != STDOUT_FILENO)
	{
		close(1);
		error += dup2(d->out, 1);
		close(d->out);
	}
	if (error < 0)
		exit_shell(d, EXIT_FAILURE);
}

static void	exec_cmd(t_data *d, t_lst *l)
{
	char	*str;
	char	**arg;

	str = ft_strdup(l->cmd);
	if (!str)
		exit_shell(d, EXIT_FAILURE);
	if (find_cmd(&str, d->env))
	{
		ft_puterr("minishell: malloc failed\n");
		free(str);
		exit_shell(d, EXIT_FAILURE);
	}
	arg = l->arg;
	l->arg = NULL;
	free_stuff(d);
	execve(str, arg, d->env);
	exec_error(str, arg, d);
}

void	child(t_data *d, t_lst *l)
{
	if (check_builtins(l->cmd))
	{
		execute_builtin(d, l);
		if (d->in != STDIN_FILENO)
			close(d->in);
		if (d->out != STDOUT_FILENO)
			close(d->out);
		exit_shell(d, EXIT_SUCCESS);
	}
	dup_fds(d);
	exec_cmd(d, l);
}
