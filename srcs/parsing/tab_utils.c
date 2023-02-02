/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenicho <mbenicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:19:46 by mbenicho          #+#    #+#             */
/*   Updated: 2023/01/31 19:19:46 by mbenicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
		free(tab[i]);
			i++;
		}
	free(tab);
	}
}

void	ft_free_redir(t_redir *ptr)
{
	int	i;

	i = 0;
	if (ptr)
	{
		while (ptr[i].str)
		{
			free(ptr[i].str);
			i++;
		}
		free(ptr);
	}
}

//temp
void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		printf("%s, ", tab[i]);
		i++;
	}
	printf("\n");
}

//temp
void	print_redir(t_redir *tab)
{
	int	i;

	i = 0;
	while (tab && tab[i].str)
	{
		printf("%s, ", tab[i].str);
		i++;
	}
	printf("\n");
}
