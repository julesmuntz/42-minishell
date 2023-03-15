/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 21:41:00 by julmuntz          #+#    #+#             */
/*   Updated: 2023/03/15 23:21:36 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_cdpath(char *dir, char *arg, t_data *d)
{
	char	*tmp;

	if (dir[ft_strlen(dir) - 1] == '/')
		tmp = galloc(ft_strjoin(dir, arg),
				(ft_strlen(dir) + ft_strlen(arg) + 1) * sizeof(char), d);
	else
	{
		tmp = galloc(ft_strjoin(dir, "/"),
				(ft_strlen(dir) + 2) * sizeof(char), d);
		tmp = galloc(ft_strjoin(tmp, arg),
				(ft_strlen(tmp) + ft_strlen(arg) + 1) * sizeof(char), d);
	}
	return (tmp);
}

static int	find_cdpath(t_data *d, t_lst *l, char *cdpath)
{
	int		i;
	char	**dirs;
	char	*tmp;

	if (!cdpath)
		return (0);
	i = 0;
	dirs = ft_split(cdpath, ':');
	while (dirs[i])
	{
		tmp = get_cdpath(dirs[i], l->arg[1], d);
		if (chdir(tmp) == 0)
			break ;
		i++;
	}
	ft_free_lines(dirs);
	if (chdir(tmp) == -1)
		return (1);
	return (0);
}

static int	cmd_cd2(t_data *d, t_lst *l, char *path)
{
	char	buf[4096];
	char	*cdpath;

	if (chdir(path) == -1)
	{
		cdpath = ft_getenv("CDPATH", d);
		if (cdpath)
		{
			if (find_cdpath(d, l, cdpath))
				return (g_exit_code = 1, ft_fprintf(STDERR_FILENO,
						"minishell: cd: %s: %s\n", l->arg[1],
						strerror(errno)), 0);
			ft_fprintf(d->out, "/%s\n", path);
		}
		else
		{
			ft_fprintf(STDERR_FILENO, "minishell: cd: %s: %s\n", l->arg[1],
				strerror(errno));
			return (g_exit_code = 1, 0);
		}
	}
	ft_setenv("OLDPWD", ft_getenv("PWD", d), d);
	ft_setenv("PWD", getcwd(buf, sizeof(buf)), d);
	g_exit_code = 0;
	return (0);
}

int	cmd_cd(t_data *d, t_lst *l)
{
	char	*path;

	if (l->arg[1] && l->arg[2])
		return (g_exit_code = 1,
			ft_puterr("minishell: cd: too many arguments\n"), 0);
	else if (!d->cwd && l->arg[1] && !access(l->arg[1], F_OK))
		return (ft_puterr("cd: error retrieving current directory: \
getcwd: cannot access parent directories: No such file or directory\n"), 0);
	else if ((!l->arg[1]) || (!ft_strcmp(l->arg[1], "~")))
		path = ft_getenv("HOME", d);
	else if (!ft_strcmp(l->arg[1], "-"))
	{
		path = ft_getenv("OLDPWD", d);
		if (!path)
			return (g_exit_code = 1,
				ft_puterr("minishell: cd: OLDPWD not set\n"), 0);
		ft_fprintf(d->out, "%s\n", path);
	}
	else
		path = l->arg[1];
	if (!path)
		return (g_exit_code = 1, ft_puterr("minishell: cd: HOME not set\n"), 0);
	return (cmd_cd2(d, l, path));
}
