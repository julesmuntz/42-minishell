/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:57:26 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/09 20:03:36 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_export(t_builtins *data, t_data *d)
{
	int	i;

	data->env_export = malloc(sizeof(char *) * ft_arrstrlen(d->env) + 1);
	if (!data->env_export)
		return ;
	i = 0;
	while (i < (int)ft_arrstrlen(d->env))
	{
		data->env_export[i] = malloc(sizeof(char) * ft_strlen(d->env[i]));
		if (!data->env_export[i])
			return (ft_free_lines(data->env_export));
		i++;
	}
	i = 0;
	while (i < (int)ft_arrstrlen(data->env_export))
	{
		data->env_export[i] = ft_strdup(d->env[i]);
		if (!data->env_export[i])
			return ;
		i++;
	}
	ft_sort_arrstr(data->env_export, (int)ft_arrstrlen(data->env_export));
	i = 0;
	while (data->env_export[i] && i < (int)ft_arrstrlen(data->env_export) - 1)
	{
		printf("declare -x %s\n", data->env_export[i]);
		i++;
	}
}
