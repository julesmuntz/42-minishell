/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 15:31:06 by julmuntz          #+#    #+#             */
/*   Updated: 2022/08/22 18:44:19 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_until_nl(char *str)
{
	int		i;
	int		len;
	char	*line;

	len = 0;
	while (str[len] != '\0' && str[len] != '\n')
		len++;
	if (str[len] == '\n')
		len++;
	line = malloc(sizeof(char) * (len + 1));
	if (line == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_post_nl(char *str)
{
	int		i;
	int		len;
	int		rest;
	char	*buf;

	i = 0;
	len = ft_strlen(str);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	if (str[i] == '\0')
		return (free(str), NULL);
	rest = len - i;
	buf = malloc(sizeof(char) * (rest + 1));
	if (buf == NULL)
		return (NULL);
	len = 0;
	while (str[i])
		buf[len++] = str[i++];
	buf[len] = '\0';
	return (free(str), buf);
}

char	*get_next_line(int fd)
{
	int			size;
	static char	buf[BUFFER_SIZE + 1];
	static char	*str;
	char		*line;

	if (fd <= -1 || fd >= FOPEN_MAX)
		return (NULL);
	size = 1;
	while (size > 0)
	{
		size = read(fd, buf, BUFFER_SIZE);
		if (size == -1 || (size == 0 && ft_strlen(str) == 0))
			return (free(str), NULL);
		buf[size] = '\0';
		if (str == NULL)
			str = ft_strdup(buf);
		else if (buf[0] != '\0')
			str = ft_strjoin(str, buf);
		if (ft_strchr(str, '\n'))
			break ;
	}
	line = ft_until_nl(str);
	str = ft_post_nl(str);
	return (line);
}
