/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:36:04 by julmuntz          #+#    #+#             */
/*   Updated: 2023/03/09 20:24:28 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*galloc(void *ptr, size_t size, t_data *d)
{
	void		*new;
	t_garbage	*new_garbage;

	if (ptr == NULL)
	{
		new = malloc(size);
		if (new == NULL)
			return (NULL);
	}
	else if (size == 0)
		return (free(ptr), NULL);
	else
	{
		new = ft_realloc(ptr, size);
		if (new == NULL)
			return (NULL);
	}
	new_garbage = malloc(sizeof(t_garbage));
	if (new_garbage != NULL)
	{
		new_garbage->ptr = new;
		new_garbage->next = d->g;
		d->g = new_garbage;
	}
	return (new);
}

void	free_garbage(t_garbage **g)
{
	t_garbage	*current;

	while (*g)
	{
		current = *g;
		*g = (*g)->next;
		free(current->ptr);
		free(current);
	}
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
	if (sig == SIGINT)
		g_exit_code = 130;
}
