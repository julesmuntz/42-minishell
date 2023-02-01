/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenicho <mbenicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:19:46 by mbenicho          #+#    #+#             */
/*   Updated: 2023/01/31 19:19:46 by mbenicho         ###   ########.fr       */
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
static int	slvl_init(char *env, char **dest)
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
	*dest = ft_strjoin("SHLVL=", str);
	free(str);
	if (!*dest)
		return (1);
	return (0);
}

char	**init_env(char **env)
{
	int		size;
	int		i;
	char	**tab;

	size = ft_arrstrlen(env);
	tab = malloc((size + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], "SHLVL=", 6) \
		&& slvl_init(env[i], &(tab[i])))
			return (ft_free_tab(tab), NULL);
		else if (ft_strncmp(env[i], "SHLVL=", 6))
		{
			tab[i] = ft_strdup(env[i]);
			if (!tab[i])
				return (ft_free_tab(tab), NULL);
		}
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
