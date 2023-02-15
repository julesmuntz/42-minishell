/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 21:41:00 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/15 14:06:11 by julmuntz         ###   ########.fr       */
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
	char	*result;

	i = -1;
	paths = ft_split(find_paths(env), ':');
	while (paths[++i])
	{
		if (!access(str, F_OK))
		{
			result = ft_strdup(str);
			ft_free_lines(paths);
			return (result);
		}
	}
	ft_free_lines(paths);
	return (0);
}

int	cmd_cd(t_data *d, t_lst *l)
{
	char	*path;

	if (!ft_strcmp(l->arg[1], "~") || !l->arg[1])
	{
		chdir(getenv("HOME"));
		return (0);
	}
	else if (!l->arg[1])
		return (0);
	if (l->arg[2])
	{
		ft_fprintf(STDERR_FILENO, "minishell: %s: too many arguments\n", l->cmd);
		return (0);
	}
	path = find_dir(l->arg[1], d->env);
	if (!path)
	{
		ft_fprintf(STDERR_FILENO, "minishell: %s:\
%s: No such file or directory\n", l->cmd, l->arg[1]);
		return (0);
	}
	chdir(l->arg[1]);
	return (0);
}
