/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:21:25 by julmuntz          #+#    #+#             */
/*   Updated: 2023/01/28 11:54:56 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_command(t_testing *data)
{
	if (ft_strnstr(data->cmd_to_execute, "echo", 4))
		cmd_echo(data);
	if (ft_strnstr(data->cmd_to_execute, "cd", 2))
		return (0);
	if (ft_strnstr(data->cmd_to_execute, "pwd", 3))
		return (0);
	if (ft_strnstr(data->cmd_to_execute, "export", 6))
		return (0);
	if (ft_strnstr(data->cmd_to_execute, "unset", 5))
		return (0);
	if (ft_strnstr(data->cmd_to_execute, "env", 3))
		return (0);
	if (ft_strnstr(data->cmd_to_execute, "exit", 4))
		return (0);
	return (0);
}

int	custom_builtins(char *file, t_testing *data)
{
	if (ft_strrstr(file, "echo\0", 5))
		data->cmd_to_execute = "echo";
	if (ft_strrstr(file, "cd\0", 3))
		data->cmd_to_execute = "cd";
	if (ft_strrstr(file, "pwd\0", 4))
		data->cmd_to_execute = "pwd";
	if (ft_strrstr(file, "export\0", 7))
		data->cmd_to_execute = "export";
	if (ft_strrstr(file, "unset\0", 6))
		data->cmd_to_execute = "unset";
	if (ft_strrstr(file, "env\0", 4))
		data->cmd_to_execute = "env";
	if (ft_strrstr(file, "exit\0", 5))
		data->cmd_to_execute = "exit";
	if (data->cmd_to_execute)
		return (TRUE);
	return (FALSE);
}

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

static char	*find_cmd(char *cmd, t_testing *data)
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
			if (custom_builtins(file, data) == TRUE)
				return (0);
			else if (!access(file, F_OK))
				return (file);
			free(file);
		}
		else
			file = cmd;
		if (custom_builtins(file, data) == TRUE)
			return (0);
		else if (!access(file, F_OK))
			return (file);
		i++;
	}
	ft_free_lines(data->paths);
	return (0);
}

static int	valid_input(char *arg, t_testing *data)
{
	data->cmd = ft_split(arg, ' ');
	if (custom_builtins(*data->cmd, data) == TRUE && !find_cmd(*data->cmd, data))
		return (CUSTOM);
	if (!find_cmd(*data->cmd, data))
	{
		printf("Error\n\
Cannot access '%s': no such file or directory.\n", *data->cmd);
		ft_free_lines(data->cmd);
		return (FALSE);
	}
	if (execve(find_cmd(*data->cmd, data), data->cmd, data->env) == -1)
		return (FALSE);
	return (TRUE);
}

int	main(int arc, char **arv, char **env)
{
	t_testing	data;

	if (arc != 2)
		return (printf("Please ENTER 1 command.\n"), FALSE);
	data.env = env;
	data.arg = arv;
	data.nbr_arg = (arc - 2);
	if (valid_input(data.arg[1], &data) == FALSE)
		return (0);
	if (valid_input(data.arg[1], &data) == CUSTOM)
		execute_command(&data);
	else if (valid_input(data.arg[1], &data) == TRUE)
		execve(find_cmd(*data.cmd, &data), data.cmd, data.env);
	return (0);
}
