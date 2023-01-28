/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:56:31 by julmuntz          #+#    #+#             */
/*   Updated: 2022/05/25 17:37:11 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_char_count(char *s, char c, int *index_chars)
{
	int	len;

	len = 0;
	while (s[*index_chars] && s[*index_chars] == c)
		(*index_chars)++;
	while (s[*index_chars + len] && s[*index_chars + len] != c)
		len++;
	return (len);
}

static int	ft_word_count(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			while (s[i] && s[i] == c)
				i++;
		}
		else
		{
			while (s[i] && s[i] != c)
				i++;
			count++;
		}
	}
	return (count);
}

char	**ft_split(char *s, char c)
{
	char	**tab;
	int		index_words;
	int		index_chars;
	int		nb_words;
	int		nb_chars;

	if (s == NULL)
		return (NULL);
	index_words = 0;
	index_chars = 0;
	nb_words = ft_word_count(s, c);
	tab = ft_calloc(sizeof(char *), (nb_words + 1));
	if (tab == NULL)
		return (NULL);
	while (index_words < nb_words)
	{
		nb_chars = ft_char_count(s, c, &index_chars);
		tab[index_words] = ft_substr(s, index_chars, nb_chars);
		index_chars += nb_chars;
		index_words++;
	}
	return (tab);
}
