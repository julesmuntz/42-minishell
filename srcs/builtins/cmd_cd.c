/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 21:41:00 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/07 20:23:04 by julmuntz         ###   ########.fr       */
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

char	*find_dir(char *str, char **env)
{
	int		i;
	char	**paths;

	i = -1;
	paths = ft_split(find_paths(env), ':');
	while (paths[++i])
	{
		if (!access(str, F_OK))
			return (str);
	}
	ft_free_lines(paths);
	return (0);
}

int	cmd_cd(t_builtins *data, t_data *d)
{
	char	*path;

	if (!ft_strcmp(data->cmd_with_path[1], "~") || !data->cmd_with_path[1])
	{
		chdir(getenv("HOME"));
		return (0);
	}
	else if (!data->cmd_with_path[1])
		return (0);
	if (data->cmd_with_path[2])
	{
		printf("bash: %s: too many arguments\n", data->cmd_with_path[0]);
		return (0);
	}
	path = find_dir(data->cmd_with_path[1], d->env);
	if (!path)
	{
		printf("bash: %s: %s: No such file or directory\n",
			data->cmd_with_path[0], data->cmd_with_path[1]);
		return (0);
	}
	chdir(data->cmd_with_path[1]);
	return (0);
}
