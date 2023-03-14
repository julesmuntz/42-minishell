/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 23:20:02 by julmuntz          #+#    #+#             */
/*   Updated: 2023/03/14 16:57:49 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_number(char *str)
{
	int	i;

	i = 0;
	if (*str == '+' || *str == '-')
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
		i++;
	}
	if (i > 19)
		return (0);
	return (1);
}

static long long	get_number(char *str)
{
	int			sign;
	long long	value;

	sign = 1;
	value = 0;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str)
	{
		if (*str < '0' || *str > '9')
			break ;
		value = value * 10 + (*str - '0');
		str++;
	}
	return (value * sign);
}

static void	get_code2(t_lst *l, int *code, int *error)
{
	if (*error && *code == 1)
		ft_fprintf(STDERR_FILENO, "minishell: exit: too many arguments\n");
	else if (*error && *code == 2)
	{
		ft_fprintf(STDERR_FILENO,
			"minishell: exit: %s: numeric argument required\n", l->arg[1]);
	}
}

static int	get_code(t_lst *l, long long *value, int *code, int *error)
{
	*error = 1;
	if (!is_number(l->arg[1]))
		*code = 2;
	else if (is_number(l->arg[1]) && l->arg[2])
		*code = 1;
	else if (is_number(l->arg[1]) && !l->arg[2])
	{
		*value = get_number(l->arg[1]);
		if (*value >= INT_MIN && *value <= INT_MAX)
		{
			*error = 0;
			*code = (int)*value % 256;
		}
		else if ((((unsigned long long)*value > LLONG_MAX)
				&& (*l->arg[1] != '-'))
			|| (((unsigned long long)*value > (unsigned long long)LLONG_MAX + 1)
				&& (*l->arg[1] == '-')))
			*code = 2;
	}
	else
		*code = 2;
	get_code2(l, code, error);
	return (*code);
}

int	cmd_exit(t_data *d, t_lst *l)
{
	int			exit_code;
	long long	value;
	int			error;

	exit_code = g_exit_code;
	value = 0;
	error = 0;
	if (d->in != STDIN_FILENO)
		close(d->in);
	if (d->out != STDOUT_FILENO)
		close(d->out);
	if (d->main)
		ft_puterr("exit\n");
	if (d->l->arg[1])
		exit_code = get_code(l, &value, &exit_code, &error);
	if (error && exit_code == 1)
		return (g_exit_code = 1, 0);
	else
		exit_shell(d, exit_code);
	return (0);
}
