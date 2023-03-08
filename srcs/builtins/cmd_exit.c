/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 23:20:02 by julmuntz          #+#    #+#             */
/*   Updated: 2023/03/08 13:42:07 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_number(const char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	if (!*str)
		return (false);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (false);
		str++;
	}
	return (true);
}

long long	get_number(const char *str)
{
	long long	value;
	int			sign;

	value = 0;
	sign = 1;
	if (*str == '-')
	{
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
	return (sign * value);
}

static int	get_code(t_data *d, unsigned long long *value, int *code)
{
	if (d->l->arg[2] != NULL)
	{
		ft_fprintf(STDERR_FILENO, "minishell: exit: too many arguments\n");
		*code = 1;
	}
	else if (is_number(d->l->arg[1]))
	{
		*value = get_number(d->l->arg[1]);
		if ((long long)*value >= INT_MIN && (long long)*value <= INT_MAX)
			*code = (int)*value % 256;
		else if (*value > LLONG_MAX)
		{
			ft_fprintf(STDERR_FILENO,
				"minishell: exit: %s: numeric argument required\n",
				d->l->arg[1]);
			*code = 2;
		}
	}
	else
	{
		ft_fprintf(STDERR_FILENO,
			"minishell: exit: %s: numeric argument required\n", d->l->arg[1]);
		*code = 2;
	}
	return (*code);
}

int	cmd_exit(t_data *d)
{
	int					exit_code;
	unsigned long long	value;

	exit_code = g_exit_code;
	value = 0;
	ft_puterr("exit\n");
	if (d->l->arg[1])
		exit_code = get_code(d, &value, &exit_code);
	exit_shell(d, exit_code);
	return (0);
}
