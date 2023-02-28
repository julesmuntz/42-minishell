/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 23:20:02 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/28 17:53:01 by julmuntz         ###   ########.fr       */
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

static int	get_code(t_data *d, long long *value, int *code)
{
	if (is_number(d->l->arg[1]))
	{
		if (*value >= INT_MIN && *value <= INT_MAX)
		{
			*value = get_number(d->l->arg[1]);
			*code = (int)*value % 256;
			if (d->l->arg[2] != NULL)
			{
				ft_fprintf(STDERR_FILENO, "minishell: exit: \
too many arguments\n");
				*code = 1;
			}
		}
		else
		{
			ft_fprintf(STDERR_FILENO, "minishell: exit: \
%s: numeric argument out of range\n", d->l->arg[1]);
			*code = 2;
		}
	}
	else
	{
		ft_fprintf(STDERR_FILENO, "minishell: exit: \
%s: numeric argument required\n", d->l->arg[1]);
		*code = 2;
	}
	return (*code);
}

int	cmd_exit(t_data *d)
{
	int			exit_code;
	long long	value;

	exit_code = g_exit_code;
	value = 0;
	write(STDERR_FILENO, "exit\n", 5);
	if (d->l->arg[1])
		exit_code = get_code(d, &value, &exit_code);
	exit_shell(d, exit_code);
	return (0);
}
