/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:19:46 by mbenicho          #+#    #+#             */
/*   Updated: 2023/03/02 01:00:08 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*itoa(int n, char *str)
{
	char	*tmp;
	char	c;

	tmp = NULL;
	if (n > 9)
	{
		str = itoa(n / 10, str);
		if (!str)
			return (NULL);
	}
	c = (n % 10) + '0';
	tmp = ft_strjoin(str, &c);
	free(str);
	return (tmp);
}

static int	slvl_init(char *env, char **dest, t_data *d)
{
	int		n;
	char	*str;

	ft_superatoi((env + 6), &n);
	n++;
	str = malloc(1);
	if (!str)
		return (*dest = NULL, 1);
	*str = 0;
	str = itoa(n, str);
	if (!str)
		return (*dest = NULL, 1);
	*dest = galloc(ft_strjoin("SHLVL=", str), ft_strlen(str) + 7, d);
	free(str);
	if (!*dest)
		return (1);
	return (0);
}

char	**init_env(char **env, t_data *d)
{
	int		size;
	int		i;
	char	**tab;

	size = ft_arrstrlen(env);
	tab = galloc(NULL, (size + 1) * sizeof(char *), d);
	if (!tab)
		return (NULL);
	i = 0;
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], "SHLVL=", 6) \
		&& slvl_init(env[i], &(tab[i]), d))
			return (NULL);
		else if (ft_strncmp(env[i], "SHLVL=", 6))
		{
			tab[i] = galloc(ft_strdup(env[i]), ft_strlen(env[i]) + 1, d);
			if (!tab[i])
				return (NULL);
		}
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

char	**update_env(t_data *d)
{
	char		**new;
	t_export	*tmp;
	int			i;

	i = 0;
	tmp = d->x;
	new = (char **)galloc(NULL, sizeof(new) * (d->env_size + 1), d);
	while (tmp)
	{
		if (!tmp->value)
		{
			tmp = tmp->next;
			continue ;
		}
		new[i] = galloc(ft_strjoin(galloc(ft_strdup(tmp->key),
						ft_strlen(tmp->key) + 1, d), "="),
				ft_strlen(tmp->key) + 2, d);
		new[i] = galloc(ft_strjoin(new[i], tmp->value), ft_strlen(new[i])
				+ ft_strlen(tmp->value) + 1, d);
		tmp = tmp->next;
		i++;
	}
	new[i] = NULL;
	return (new);
}
