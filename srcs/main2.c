/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:36:04 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/05 22:18:46 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exe_cmd(t_data *d)
{
	char	**cmd;

	cmd = d->l->arg;
	if (!get_cmd(cmd, d))
		return (ft_lst_free(d->l), exit_shell(d, EXIT_SUCCESS), 1);
	return (0);
}

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
			&& cur_dir[ft_strlen(user)] == '/' )
		{
			if (!ft_strnstr(cur_dir, user, i))
				gap = (ft_strlen(user) + i);
		}
		i++;
	}
	return (gap);
}

void	refresh_prompt(t_data *d)
{
	int		gap;
	char	*tmp;
	char	*cur_dir;
	char	*tilde;

	gap = 0;
	tilde = "";
	cur_dir = getcwd(malloc(sizeof(char) * 4096), 4096);
	gap = user_dir_name(cur_dir);
	if (gap)
		tilde = "~";
	tmp = ft_strjoin(COLOR, ft_strjoin(getenv("USER"),
				ft_strjoin(PROMPT COLOR_RESET, ft_strjoin(tilde,
						ft_strjoin(cur_dir + gap,
							COLOR "$ " COLOR_RESET)))));
	d->prompt = ft_strdup(tmp);
	free(cur_dir);
	free(tmp);
}
