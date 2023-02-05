/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 21:41:00 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/05 20:58:49 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_paths(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH", 4))
			return (env[i] + 5);
		i++;
	}
	return (0);
}

static char	*find_dir(char *str, char **env, t_builtins *data)
{
	int		i;
	char	*path;
	char	**paths;

	i = -1;
	paths = ft_split(find_paths(env), ':');
	while (paths[++i])
	{
		if (!access(str, F_OK))
		{
			printf("\t%s\n", str);
			return (data->cmd_path);
		}
	}
	ft_free_lines(paths);
	return (0);
}

int	cmd_cd(t_builtins *data, t_data *d)
{
	char	*path;

	if (data->cmd[2])
	{
		printf("bash: %s: too many arguments\n", data->cmd[0]);
		return (0);
	}
	path = find_dir(data->cmd[1], d->env, data);
	if (!path)
	{
		printf("bash: %s: %s: No such file or directory\n",
			data->cmd[0], data->cmd[1]);
		return (0);
	}
	chdir(data->cmd[1]);
	return (0);
}
