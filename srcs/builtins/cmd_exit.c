/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 23:20:02 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/06 01:00:37 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_exit(t_builtins *data, t_data *d)
{
	if (!ft_strcmp(*data->cmd, "exit"))
	{
		write(1, "exit\n", 5);
		exit_shell(d, EXIT_SUCCESS);
		return ;
	}
}
