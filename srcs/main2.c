/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:36:04 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/09 13:02:06 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exe_cmd(t_data *d)
{
	char	**no_path;
	char	**with_path;

	no_path = d->l->arg;
	with_path = d->l->arg_path;
	if (!get_cmd(no_path, with_path, d))
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

int	refresh_prompt(t_data *d)
{
	int		gap;
	char	*tmp;
	char	*cur_dir;
	char	path[4096];
	char	*tilde;

	gap = 0;
	tilde = "";
	cur_dir = getcwd(path, 4096);
	gap = user_dir_name(cur_dir);
	if (gap)
		tilde = "~";
	tmp = ft_bigcat(getenv("USER"), COLOR PROMPT COLOR_RESET, tilde,
			ft_strcat(cur_dir + gap, COLOR "$ " COLOR_RESET));
	if (!tmp)
		return (1);
	d->prompt = ft_strdup(tmp);
	if (!d->prompt)
		return (free(tmp), 1);
	free(tmp);
	return (0);
}

void	handle_signals(int sig)
{
	if (sig == SIGINT)
		return ;
}
