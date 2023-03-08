/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 18:43:54 by mbenicho          #+#    #+#             */
/*   Updated: 2023/03/08 11:17:42 by julmuntz         ###   ########.fr       */
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

static void	child_exit_error(char *str, char **arg, t_data *d, int error)
{
	free(str);
	ft_free_tab(arg);
	free_garbage(&d->g);
	exit(error);
}

static int	error_code(int error)
{
	if (error == 2)
		return (127);
	if (error == 13)
		return (126);
	return (error);
}

void	exec_error(char *str, char **arg, t_data *d)
{
	int			error;
	struct stat	*buf;

	error = errno;
	if (((error == 2 && !ft_strchr(str, '/')) \
	|| !ft_strcmp(str, ".") || !ft_strcmp(str, "..")))
		ft_fprintf(STDERR_FILENO, "minishell: %s: command not found\n", str);
	else if (error == 13)
	{
		buf = malloc(sizeof(struct stat));
		if (!buf)
			ft_puterr("Error when calling malloc\n");
		else if (stat(str, buf) && errno != EACCES)
			ft_puterr("Error when calling stat\n");
		else if (S_ISDIR(buf->st_mode))
			ft_fprintf(STDERR_FILENO, "minishell: %s: is a directory\n", str);
		else
			ft_fprintf(STDERR_FILENO, \
			"minishell: %s: %s\n", str, strerror(error));
		free(buf);
	}
	else
		ft_fprintf(STDERR_FILENO, "minishell: %s: %s\n", str, strerror(error));
	error = error_code(error);
	child_exit_error(str, arg, d, error);
}
