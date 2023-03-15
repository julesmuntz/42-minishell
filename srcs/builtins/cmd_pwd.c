/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:31:40 by julmuntz          #+#    #+#             */
/*   Updated: 2023/03/14 23:52:16 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_pwd(t_data *d)
{
	char	path[4096];

	if (!d->cwd)
		return (ft_puterr("pwd: error retrieving current directory: \
getcwd: cannot access parent directories: No such file or directory\n"), 0);
	ft_fprintf(d->out, "%s\n", getcwd(path, sizeof(path)));
	g_exit_code = 0;
	return (0);
}
