/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:31:40 by julmuntz          #+#    #+#             */
/*   Updated: 2023/03/08 13:42:30 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_pwd(t_data *d)
{
	char	path[4096];

	ft_fprintf(d->out, "%s\n", getcwd(path, sizeof(path)));
	g_exit_code = 0;
	return (0);
}
