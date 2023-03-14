/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:27:16 by mbenicho          #+#    #+#             */
/*   Updated: 2023/03/14 18:14:28 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_builtins(t_data *d)
{
	int	err;

	if (!d->l->next && check_builtins(d->l->cmd))
	{
		err = redirect(d, d->l);
		if (d->heredoc)
		{
			d->heredoc = 0;
			unlink(".heredoc.tmp");
		}
		if (err)
			return (g_exit_code = 1, 1);
		execute_builtin(d, d->l);
		return (1);
	}
	return (0);
}

static int	wait_childs(t_data *d)
{
	t_lst	*tmp;
	int		wstatus;

	tmp = d->l;
	while (tmp)
	{
		if (tmp->called)
		{
			waitpid(tmp->pid, &wstatus, 0);
			if (g_exit_code == -1)
				g_exit_code = 130;
			else if (g_exit_code == -2)
				g_exit_code = 131;
			else if (WIFEXITED(wstatus))
				g_exit_code = WEXITSTATUS(wstatus);
		}
		tmp = tmp->next;
	}
	return (0);
}

static void	open_pipes(t_data *d, t_lst *tmp, int *pipe_err, int *error)
{
	if (tmp == d->l)
		d->in = STDIN_FILENO;
	else if (!*pipe_err)
	{
		close(d->pipefd[1]);
		d->in = d->pipe;
	}
	if (tmp->next && !*pipe_err)
	{
		if (pipe(d->pipefd))
		{
			*pipe_err = 1;
			ft_fprintf(STDERR_FILENO, "minishell: %s\n", strerror(errno));
		}
		d->out = d->pipefd[1];
		d->pipe = d->pipefd[0];
	}
	else
		d->out = STDOUT_FILENO;
	if (!*pipe_err && redirect(d, tmp))
	{
		*error = 1;
		g_exit_code = 1;
	}
}

static void	call_childs(t_data *d, t_lst *tmp, int *pipe_err, int *error)
{
	if (!*pipe_err && !*error && tmp->cmd)
	{
		tmp->pid = fork();
		if (tmp->pid == 0)
		{
			if (tmp->next)
				close(d->pipe);
			d->main = 0;
			child(d, tmp);
			d->main = 1;
		}
		if (tmp->pid == -1)
			ft_fprintf(STDERR_FILENO, "minishell: %s\n", strerror(errno));
		else
			tmp->called = 1;
	}
	if (d->heredoc)
	{
		d->heredoc = 0;
		unlink(".heredoc.tmp");
	}
	if (d->in != STDIN_FILENO && d->in != -1)
		close(d->in);
	if (d->out != STDOUT_FILENO && d->out != -1)
		close(d->out);
}

int	exe_cmd(t_data *d)
{
	t_lst	*tmp;
	int		pipe_err;
	int		error;

	d->heredoc = 0;
	pipe_err = 0;
	if (!d->l)
		return (0);
	if (handle_builtins(d))
		return (0);
	signal(SIGQUIT, &handle_ctrls);
	signal(SIGINT, &handle_ctrls);
	tmp = d->l;
	while (tmp)
	{
		tmp->called = 0;
		error = 0;
		open_pipes(d, tmp, &pipe_err, &error);
		call_childs(d, tmp, &pipe_err, &error);
		tmp = tmp->next;
	}
	wait_childs(d);
	return (0);
}
