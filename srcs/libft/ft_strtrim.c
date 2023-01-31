/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenicho <mbenicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 18:25:32 by mbenicho          #+#    #+#             */
/*   Updated: 2023/01/31 18:52:28 by mbenicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ischar(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	char	*str;
	int		i;
	int		j;
	int		size;

	i = 0;
	j = ft_strlen(s1) - 1;
	while (ft_ischar(s1[i], set) && s1[i])
		i++;
	while (ft_ischar(s1[j], set) && j > 0)
		j--;
	size = j - i + 1;
	if (size < 0)
		size = 0;
	str = malloc((size + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1 + i, size + 1);
	return (str);
}
