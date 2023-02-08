/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 23:16:32 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/08 15:06:57 by julmuntz         ###   ########.fr       */
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

char	*find_cmd(char *str, char **env, t_builtins *data)
{
	int		i;
	char	*path;
	char	**paths;

	i = -1;
	paths = ft_split(find_paths(env), ':');
	while (paths[++i])
	{
		if (!ft_strchr(str, '/'))
		{
			path = ft_strjoin(paths[i], "/");
			data->cmd_path = ft_strjoin(path, str);
			free(path);
			if (!access(data->cmd_path, F_OK))
				return (data->cmd_path);
		}
		else
			data->cmd_path = str;
		if (!access(data->cmd_path, F_OK))
			return (data->cmd_path);
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
	if (!find_cmd(*data->cmd_with_path, d->env, data))
	{
		if (ft_strchr(*data->cmd_with_path, '/'))
			printf("bash: %s: No such file or directory\n",
				*data->cmd_with_path);
		else
			printf("%s: command not found\n", *data->cmd_with_path);
		return (FALSE);
	}
	if (execve(find_cmd(*data->cmd, d->env, data), data->cmd, d->env) == -1)
		return (FALSE);
	return (TRUE);
}

int	execute_builtin(t_builtins *data, t_data *d)
{
	if (!ft_strncmp(data->cmd_to_execute, "echo", 4))
		cmd_echo(data, d);
	else if (!ft_strncmp(data->cmd_to_execute, "cd", 2))
		cmd_cd(data, d);
	else if (!ft_strncmp(data->cmd_to_execute, "pwd", 3))
		cmd_pwd();
	else if (!ft_strncmp(data->cmd_to_execute, "export", 6))
		return (0);
	else if (!ft_strncmp(data->cmd_to_execute, "unset", 5))
		return (0);
	else if (!ft_strncmp(data->cmd_to_execute, "env", 3))
		cmd_env(d->env);
	else if (!ft_strncmp(data->cmd_to_execute, "exit", 4))
		cmd_exit(data, d);
	return (0);
}
