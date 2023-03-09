/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 23:20:02 by julmuntz          #+#    #+#             */
/*   Updated: 2023/03/09 15:22:50 by julmuntz         ###   ########.fr       */
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
	long long	value;

	value = 0;
	if (*str == '-')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			break ;
		value = value * 10 + (*str - '0');
		str++;
	}
	return (value);
}

static void	get_code2(t_data *d, int *code, int *error)
{
	if (*error && *code == 1)
		ft_fprintf(STDERR_FILENO, "minishell: exit: too many arguments\n");
	else if (*error && *code == 2)
	{
		ft_fprintf(STDERR_FILENO,
			"minishell: exit: %s: numeric argument required\n", d->l->arg[1]);
	}
	else if (!*error && (*code != 1 || *code != 2))
		error = 0;
}

static int	get_code(t_data *d, long long *value, int *code, int *error)
{
	*error = 1;
	if (!is_number(d->l->arg[1]))
		*code = 2;
	else if (is_number(d->l->arg[1]) && d->l->arg[2])
		*code = 1;
	else if (is_number(d->l->arg[1]) && !d->l->arg[2])
	{
		*value = get_number(d->l->arg[1]);
		if (*value >= INT_MIN && *value <= INT_MAX)
		{
			*error = 0;
			*code = (int)*value % 256;
		}
		else if ((((unsigned long long)*value > LLONG_MAX)
				&& (*d->l->arg[1] != '-'))
			|| (((unsigned long long)*value > (unsigned long long)LLONG_MAX + 1)
				&& (*d->l->arg[1] == '-')))
			*code = 2;
	}
	else
		*code = 2;
	get_code2(d, code, error);
	return (*code);
}

int	cmd_exit(t_data *d)
{
	int			exit_code;
	long long	value;
	int			error;

	exit_code = g_exit_code;
	value = 0;
	error = 0;
	ft_puterr("exit\n");
	if (d->l->arg[1])
		exit_code = get_code(d, &value, &exit_code, &error);
	if (error && exit_code == 1)
		return (g_exit_code = 1, 0);
	else
		exit_shell(d, exit_code);
	return (0);
}
