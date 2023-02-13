/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:36:04 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/13 20:11:58 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	user_dir_name(char *cur_dir)
{
	int		i;
	int		gap;
	char	*user;

	i = 0;
	gap = 0;
	user = getenv("USER");
	while (cur_dir[i])
	{
		if (cur_dir[i] == user[0]
			&& cur_dir[i + (ft_strlen(user) - 1)]
			== user[(ft_strlen(user) - 1)]
			&& cur_dir[ft_strlen(user)] == '/')
		{
			if (!ft_strnstr(cur_dir, user, i))
				gap = (ft_strlen(user) + i);
		}
		i++;
	}
	return (gap);
}

int	refresh_prompt(t_data *d)
{
	int		gap;
	char	*tmp;
	char	*cur_dir;
	char	path[4096];

	gap = 0;
	gap = user_dir_name(getcwd(path, 4096));
	cur_dir = getcwd(path, 4096);
	if (gap != 0)
	{
		tmp = ft_bigcat(COLOR_A, getenv("USER"), COLOR_B PROMPT COLOR_C "~",
				ft_strcat(cur_dir + gap, COLOR_D "$ " COLOR_E));
	}
	else
	{
		tmp = ft_bigcat(COLOR_A, getenv("USER"), COLOR_B PROMPT COLOR_C "",
				ft_strcat(cur_dir, COLOR_D "$ " COLOR_E));
	}
	if (!tmp)
		return (1);
	d->prompt = ft_strdup(tmp);
	if (!d->prompt)
		return (free(tmp), 1);
	free(tmp);
	return (0);
}

void	handle_ctrl_c(int sig)
{
	(void)sig;
	signal(SIGINT, handle_ctrl_c);
	ft_fprintf(STDOUT_FILENO, "\n");
}
