/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 18:43:54 by mbenicho          #+#    #+#             */
/*   Updated: 2023/03/15 00:14:08 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_stuff(t_data *d)
{
	rl_clear_history();
	ft_lst_free(d->l);
	free(d->tmp);
}

void	child_exit_error(char *str, char **arg, t_data *d, int error)
{
	free(str);
	ft_free_tab(arg);
	free_garbage(&d->g);
	exit(error);
}

static int	permission_error(char *str)
{
	struct stat	*buf;

	buf = malloc(sizeof(struct stat));
	if (!buf)
		return (ft_puterr("minishell: malloc failed\n"), 1);
	else if (stat(str, buf) && errno != EACCES)
		return (ft_puterr("minishell: malloc failed\n"), 1);
	else if (S_ISDIR(buf->st_mode))
	{
		ft_fprintf(STDERR_FILENO, "minishell: %s: is a directory\n", str);
		return (free(buf), 126);
	}
	else if (!access(str, X_OK))
		return (free(buf), 0);
	ft_fprintf(STDERR_FILENO, \
	"minishell: %s: permission denied\n", str);
	return (free(buf), 126);
}

void	exec_error(char *str, char **arg, t_data *d)
{
	int			error;

	error = 0;
	if ((!ft_strchr(str, '/')) \
	|| !ft_strcmp(str, ".") || !ft_strcmp(str, ".."))
	{
		ft_fprintf(STDERR_FILENO, "minishell: %s: command not found\n", str);
		if (!ft_strcmp(str, "."))
			error = 2;
		else
			error = 127;
	}
	else if (!access(str, F_OK))
		error = permission_error(str);
	else
	{
		ft_fprintf(STDERR_FILENO, "minishell: %s: no such file or directory\n",
			str);
		error = 127;
	}
	if (error)
		child_exit_error(str, arg, d, error);
}
