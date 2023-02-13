/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:11:22 by mbenicho          #+#    #+#             */
/*   Updated: 2023/02/13 17:31:24 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_paths(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			return (env[i] + 5);
		i++;
	}
	return (0);
}

int	find_cmd(char **str, char **env)
{
	int		i;
	char	*path;
	char	**paths;
	char	*cmd_path;

	i = -1;
	if (ft_strchr(*str, '/'))
		return (0);
	paths = ft_split(find_paths(env), ':');
	if (!paths)
		return (1);
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], "/");
		if (!path)
			return (ft_free_lines(paths), 1);
		cmd_path = ft_strjoin(path, *str);
		free(path);
		if (!cmd_path)
			return (ft_free_lines(paths), 1);
		if (access(cmd_path, F_OK) == 0)
			return (ft_free_lines(paths), free(*str), *str = cmd_path, 1);
		free(cmd_path);
	}
	return (ft_free_lines(paths), 0);
}
