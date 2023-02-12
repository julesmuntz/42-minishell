/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 23:16:32 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/12 02:08:29 by julmuntz         ###   ########.fr       */
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

static int	custom_builtins(char *str, t_builtins *data)
{
	if (!ft_strcmp(str, "exit"))
		return (data->cmd_to_execute = "exit", TRUE);
	else if (!ft_strcmp(str, "echo"))
		return (data->cmd_to_execute = "echo", TRUE);
	else if (!ft_strcmp(str, "cd"))
		return (data->cmd_to_execute = "cd", TRUE);
	else if (!ft_strcmp(str, "pwd"))
		return (data->cmd_to_execute = "pwd", TRUE);
	else if (!ft_strcmp(str, "export"))
		return (data->cmd_to_execute = "export", TRUE);
	else if (!ft_strcmp(str, "unset"))
		return (data->cmd_to_execute = "unset", TRUE);
	else if (!ft_strcmp(str, "env"))
		return (data->cmd_to_execute = "env", TRUE);
	return (0);
}

int	valid_input(t_builtins *data, t_data *d)
{
	if (custom_builtins(*data->cmd, data) == TRUE)
		return (CUSTOM);
	if (!find_cmd(*data->cmd_with_path, d->env))
	{
		if (ft_strchr(*data->cmd_with_path, '/'))
			printf("bash: %s: No such file or directory\n",
					*data->cmd_with_path);
		else
			printf("%s: command not found\n", *data->cmd_with_path);
		return (FALSE);
	}
	if (execve(find_cmd(*data->cmd, d->env), data->cmd, d->env) == -1)
		return (FALSE);
	return (TRUE);
}

int	execute_builtin(t_builtins *data, t_export *node, t_data *d)
{
	if (!ft_strncmp(data->cmd_to_execute, "echo", 4))
		return (cmd_echo(data, d), 1);
	else if (!ft_strncmp(data->cmd_to_execute, "cd", 2))
		return (cmd_cd(data, d), 1);
	else if (!ft_strncmp(data->cmd_to_execute, "pwd", 3))
		return (cmd_pwd(), 1);
	else if (!ft_strncmp(data->cmd_to_execute, "export", 6))
		return (cmd_export(data, node), 1);
	else if (!ft_strncmp(data->cmd_to_execute, "unset", 5))
		return (0);
	else if (!ft_strncmp(data->cmd_to_execute, "env", 3))
		return (cmd_env(data, node), 1);
	else if (!ft_strncmp(data->cmd_to_execute, "exit", 4))
		return (cmd_exit(data, d), 1);
	return (0);
}
