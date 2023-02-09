/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bigcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:47:42 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/09 12:34:18 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_bigcat(char *s1, char *s2, char *s3, char *s4)
{
	char	*tmp;
	char	*part1;
	char	*part2;
	char	*full;

	tmp = ft_strjoin(s1, s2);
	part1 = ft_strdup(tmp);
	free(tmp);
	tmp = ft_strjoin(s3, s4);
	part2 = ft_strdup(tmp);
	free(tmp);
	tmp = ft_strjoin(part1, part2);
	full = ft_strdup(tmp);
	if (!full)
		return (free(tmp), free(part1), free(part2), NULL);
	free(tmp);
	free(part1);
	free(part2);
	return (full);
}
