/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 23:16:32 by julmuntz          #+#    #+#             */
/*   Updated: 2023/01/29 18:40:28 by julmuntz         ###   ########.fr       */
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

static char	*find_cmd(char *cmd, t_builtins *data)
{
	int		i;
	char	*file;
	char	*filepath;

	i = 0;
	data->paths = ft_split(find_paths(data->env), ':');
	while (data->paths[i])
	{
		if (!ft_strchr(cmd, '/'))
		{
			filepath = ft_strjoin(data->paths[i], "/");
			file = ft_strjoin(filepath, cmd);
			free(filepath);
			if (!access(file, F_OK))
				return (file);
			free(file);
		}
		else
			file = cmd;
		if (!access(file, F_OK))
			return (file);
		i++;
	}
	ft_free_lines(data->paths);
	return (0);
}

static int	custom_builtins(char *cmd, t_builtins *data)
{
	if (ft_isspace_null(cmd[4]) && !ft_strncmp(cmd, "echo", 4))
		data->cmd_to_execute = "echo";
	else if (ft_isspace_null(cmd[2]) && !ft_strncmp(cmd, "cd", 2))
		data->cmd_to_execute = "cd";
	else if (ft_isspace_null(cmd[3]) && !ft_strncmp(cmd, "pwd", 3))
		data->cmd_to_execute = "pwd";
	else if (ft_isspace_null(cmd[6]) && !ft_strncmp(cmd, "export", 6))
		data->cmd_to_execute = "export";
	else if (ft_isspace_null(cmd[5]) && !ft_strncmp(cmd, "unset", 5))
		data->cmd_to_execute = "unset";
	else if (ft_isspace_null(cmd[3]) && !ft_strncmp(cmd, "env", 3))
		data->cmd_to_execute = "env";
	else if (ft_isspace_null(cmd[4]) && !ft_strncmp(cmd, "exit", 4))
		data->cmd_to_execute = "exit";
	else
		return (FALSE);
	return (TRUE);
}

int	valid_input(t_builtins *data)
{
	if (custom_builtins(*data->cmd, data) == TRUE)
		return (CUSTOM);
	if (!find_cmd(*data->cmd, data))
	{
		if (ft_strchr(*data->cmd, '/'))
			printf("bash: %s: No such file or directory\n", *data->cmd);
		else
			printf("%s: command not found\n", *data->cmd);
		ft_free_lines(data->cmd);
		return (FALSE);
	}
	if (execve(find_cmd(*data->cmd, data), data->cmd, data->env) == -1)
		return (FALSE);
	return (TRUE);
}

int	execute_builtin(t_builtins *data)
{
	if (!ft_strncmp(data->cmd_to_execute, "echo", 4))
		cmd_echo(data);
	else if (!ft_strncmp(data->cmd_to_execute, "cd", 2))
		return (0);
	else if (!ft_strncmp(data->cmd_to_execute, "pwd", 3))
		cmd_pwd();
	else if (!ft_strncmp(data->cmd_to_execute, "export", 6))
		return (0);
	else if (!ft_strncmp(data->cmd_to_execute, "unset", 5))
		return (0);
	else if (!ft_strncmp(data->cmd_to_execute, "env", 3))
		cmd_env(data);
	else if (!ft_strncmp(data->cmd_to_execute, "exit", 4))
		return (0);
	else
		execve(find_cmd(*data->cmd, data), data->cmd, data->env);
	return (0);
}
