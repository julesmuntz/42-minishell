/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:27:16 by mbenicho          #+#    #+#             */
/*   Updated: 2023/02/13 20:56:52 by julmuntz         ###   ########.fr       */
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

static void	error(char *str, t_data *d)
{
	if (!ft_strcmp(str, ".") || !ft_strcmp(str, ".."))
	{
		ft_fprintf(STDERR_FILENO, "%s: command not found\n", str);
		free(str);
		exit_shell(d, EXIT_FAILURE);
	}
	else if (!find_cmd(&str, d->env))
	{
		if (find_dir(str, d->env))
			ft_fprintf(STDERR_FILENO, "bash: %s: Is a directory\n", str);
		else if (ft_strchr(str, '/'))
			ft_fprintf(STDERR_FILENO, "bash: %s: No such file or directory\n",
				str);
		else
			ft_fprintf(STDERR_FILENO, "%s: command not found\n", str);
		free(str);
		exit_shell(d, EXIT_FAILURE);
	}
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
	str = ft_strdup(l->cmd);
	error(str, d);
	arg = l->arg;
	l->arg = NULL;
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
