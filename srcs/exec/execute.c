/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:27:16 by mbenicho          #+#    #+#             */
/*   Updated: 2023/03/02 00:56:10 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_stuff(t_data *d)
{
	rl_clear_history();
	free(d->prompt);
	ft_lst_free(d->l);
	free(d->tmp);
}

void	exec_error(char *str, char **arg, t_data *d)
{
	int		error;
	struct stat	*buf;

	error = errno;
	if ((errno == 2 && !ft_strchr(str, '/')) || !ft_strcmp(str, ".") || !ft_strcmp(str, ".."))
		ft_fprintf(STDERR_FILENO, "minishell: %s: command not found\n", arg[0]);
	else if (error == 13)
	{
		buf = malloc(sizeof(struct stat));
		if (!buf)
			write(2, "Error when calling malloc\n", 26);
		else if (stat(str, buf) && errno != EACCES)
			write(STDERR_FILENO, "Error when calling stat\n", 24);
		else if (S_ISDIR(buf->st_mode))
			ft_fprintf(STDERR_FILENO, "minishell: %s: is a directory\n", str);
		else
			ft_fprintf(STDERR_FILENO, "minishell: %s: %s\n", str, strerror(error));
		free(buf);
	}
	else
		ft_fprintf(STDERR_FILENO, "minishell: %s: %s\n", str, strerror(error));
	free(str);
	ft_free_tab(arg);
	free_garbage(&d->g);
	exit(EXIT_SUCCESS);
}

void	child(t_data *d, t_lst *l)
{
	char	*str;
	char	**arg;
	int		error;

	error = 0;
	if (check_builtins(l->cmd))
	{
		execute_builtin(d, l);
		if (d->in != STDIN_FILENO)
			close(d->in);
		if (d->out != STDOUT_FILENO)
			close(d->out);
		exit_shell(d, EXIT_SUCCESS);
	}
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
	str = ft_strdup(l->cmd);
	if (!str)
		exit_shell(d, EXIT_FAILURE);
	if (find_cmd(&str, d->env))
	{
		free(str);
		exit_shell(d, EXIT_FAILURE);
	}
	arg = l->arg;
	l->arg = NULL;
	free_stuff(d);
	d->env = update_env(d);
	execve(str, arg, d->env);
	exec_error(str, arg, d);
}

int	exe_cmd(t_data *d)
{
	t_lst	*tmp;
	int		pipefd[2];

	if (!d->l)
		return (0);
	if (!d->l->next && check_builtins(d->l->cmd))
	{
		redirect(d, d->l);
		if (execute_builtin(d, d->l))
			return (1);
		if (d->in != STDIN_FILENO)
			close(d->in);
		if (d->out != STDOUT_FILENO)
			close(d->out);
		return (0);
	}
	tmp = d->l;
	while (tmp)
	{
		if (tmp == d->l)
			d->in = STDIN_FILENO;
		else
		{
			close(pipefd[1]);
			d->in = d->pipe;
		}
		if (tmp->next)
		{
			pipe(pipefd);
			d->out = pipefd[1];
			d->pipe = pipefd[0];
		}
		else
			d->out = STDOUT_FILENO;
		redirect(d, tmp);
		tmp->pid = fork();
		if (tmp->pid == 0)
		{
			if (tmp->next)
				close(d->pipe);
			child(d, tmp);
		}
		if (d->in != STDIN_FILENO)
			close(d->in);
		if (d->out != STDOUT_FILENO)
			close(d->out);
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
