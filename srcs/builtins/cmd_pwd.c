/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:31:40 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/13 20:22:07 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_pwd(void)
{
	char	path[4096];

	ft_fprintf(STDOUT_FILENO, "%s\n", getcwd(path, sizeof(path)));
	return (0);
}
