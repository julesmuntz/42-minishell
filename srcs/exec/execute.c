/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:27:16 by mbenicho          #+#    #+#             */
/*   Updated: 2023/02/12 19:21:36 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_stuff(t_data *d)
{
	rl_clear_history();
	free(d->prompt);
	free_export(d->x);
	ft_lst_free(d->l);
	free(d->tmp);
}

void	child(t_data *d, t_lst *l)
{
	char	*str;
	char	**arg;

	if (check_builtins(l->cmd))
	{
		execute_builtin(d, l);
		exit_shell(d, EXIT_SUCCESS);
	}
	str = strdup(l->cmd);
	arg = l->arg;
	l->arg = NULL;
	if (find_cmd(&str, d->env))
	{
		write(2, "Unexpected error\n", 17);
		free(str);
		exit_shell(d, EXIT_FAILURE);
	}
	free_stuff(d);
	execve(str, arg, d->env);
	free(str);
	ft_free_tab(arg);
	exit(EXIT_FAILURE);
}

int	exe_cmd(t_data *d)
{
	t_lst	*tmp;

	if (!d->l)
		return (0);
	if (!d->l->next && check_builtins(d->l->cmd))
		return (execute_builtin(d, d->l), 0);
	tmp = d->l;
	while (tmp)
	{
		tmp->pid = fork();
		if (tmp->pid == 0)
			child(d, tmp);
		tmp = tmp->next;
	}
	tmp = d->l;
	while (tmp)
	{
		waitpid(tmp->pid, NULL, 0);
		tmp = tmp->next;
	}
	return (0);
}