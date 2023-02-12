/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 23:16:32 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/12 17:13:42 by julmuntz         ###   ########.fr       */
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

char	*find_cmd(char *str, char **env)
{
	int		i;
	char	*path;
	char	**paths;
	char	*cmd_path;

	i = -1;
	paths = ft_split(find_paths(env), ':');
	while (paths[++i])
	{
		if (!ft_strchr(str, '/'))
		{
			path = ft_strjoin(paths[i], "/");
			cmd_path = ft_strjoin(path, str);
			free(path);
			if (!access(cmd_path, F_OK))
				return (cmd_path);
		}
		else
			cmd_path = str;
		if (!access(cmd_path, F_OK))
			return (cmd_path);
	}
	ft_free_lines(paths);
	return (0);
}

int	check_builtins(char *str)
{
	if (!ft_strcmp(str, "exit"))
		return (1);
	else if (!ft_strcmp(str, "echo"))
		return (1);
	else if (!ft_strcmp(str, "cd"))
		return (1);
	else if (!ft_strcmp(str, "pwd"))
		return (1);
	else if (!ft_strcmp(str, "export"))
		return (1);
	else if (!ft_strcmp(str, "unset"))
		return (1);
	else if (!ft_strcmp(str, "env"))
		return (1);
	return (0);
}

int	execute_builtin(t_data *d, t_lst *l)
{
	if (!ft_strcmp(l->cmd, "echo"))
		cmd_echo(l);
	else if (!ft_strcmp(l->cmd, "cd"))
		cmd_cd(d, l);
	else if (!ft_strcmp(l->cmd, "pwd"))
		cmd_pwd();
	else if (!ft_strcmp(l->cmd, "export"))
		cmd_export(d, l);
	else if (!ft_strcmp(l->cmd, "unset"))
		return (0);
	else if (!ft_strcmp(l->cmd, "env"))
		cmd_env(d, l);
	else if (!ft_strcmp(l->cmd, "exit"))
		cmd_exit(d);
	return (0);
}
