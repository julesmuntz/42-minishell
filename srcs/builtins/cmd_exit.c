/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 23:20:02 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/23 18:20:35 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_exit(t_data *d)
{
	write(d->out, "exit\n", 5);
	close(d->out);
	exit_shell(d, EXIT_SUCCESS);
	return (0);
}
