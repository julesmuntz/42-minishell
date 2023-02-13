/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 21:41:00 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/13 16:09:01 by julmuntz         ###   ########.fr       */
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

int	cmd_cd(t_data *d, t_lst *l)
{
	char	*path;

	if (!ft_strcmp(l->arg_d[1], "~") || !l->arg_d[1])
	{
		chdir(getenv("HOME"));
		return (0);
	}
	else if (!l->arg_d[1])
		return (0);
	if (l->arg[2])
	{
		printf("bash: %s: too many arguments\n", l->cmd);
		return (0);
	}
	path = find_dir(l->arg_d[1], d->env);
	if (!path)
	{
		printf("bash: %s: %s: No such file or directory\n",
			l->cmd, l->arg_d[1]);
		return (0);
	}
	chdir(l->arg_d[1]);
	return (0);
}
