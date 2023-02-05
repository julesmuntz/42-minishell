/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 23:16:32 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/05 21:46:24 by julmuntz         ###   ########.fr       */
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
	if (ft_isspace_null(str[4]) && !ft_strncmp(str, "echo", 4))
		data->cmd_to_execute = "echo";
	else if (ft_isspace_null(str[2]) && !ft_strncmp(str, "cd", 2))
		data->cmd_to_execute = "cd";
	else if (ft_isspace_null(str[3]) && !ft_strncmp(str, "pwd", 3))
		data->cmd_to_execute = "pwd";
	else if (ft_isspace_null(str[6]) && !ft_strncmp(str, "export", 6))
		data->cmd_to_execute = "export";
	else if (ft_isspace_null(str[5]) && !ft_strncmp(str, "unset", 5))
		data->cmd_to_execute = "unset";
	else if (ft_isspace_null(str[3]) && !ft_strncmp(str, "env", 3))
		data->cmd_to_execute = "env";
	else if (ft_isspace_null(str[4]) && !ft_strncmp(str, "exit", 4))
		data->cmd_to_execute = "exit";
	else
		return (FALSE);
	return (TRUE);
}

int	valid_input(t_builtins *data, t_data *d)
{
	if (custom_builtins(*data->cmd, data) == TRUE)
		return (CUSTOM);
	if (!find_cmd(*data->cmd, d->env, data))
	{
		if (ft_strchr(*data->cmd, '/'))
			printf("bash: %s: No such file or directory\n", *data->cmd);
		else
			printf("%s: command not found\n", *data->cmd);
		return (FALSE);
	}
	if (execve(find_cmd(*data->cmd, d->env, data), data->cmd, d->env) == -1)
		return (TRUE);
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
		return (0);
	return (0);
}
