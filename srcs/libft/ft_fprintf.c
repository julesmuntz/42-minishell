/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 19:41:52 by julmuntz          #+#    #+#             */
/*   Updated: 2023/03/13 19:17:02 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	convert_c(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

static int	convert_s(char *s, int fd)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (s[i])
		ft_putchar_fd(s[i++], fd);
	return (i);
}

static int	convert_d(int d, int fd)
{
	int	len;

	if (d == INT_MIN)
		return (write(fd, "-2147483648", 11));
	len = ft_nbrlen(d);
	ft_putnbr_fd(d, fd);
	return (len);
}

static int	convert(va_list ap, int type, int fd)
{
	if (type == 'c')
		return (convert_c((char)va_arg(ap, int), fd));
	if (type == 's')
		return (convert_s(va_arg(ap, char *), fd));
	if (type == 'd')
		return (convert_d(va_arg(ap, int), fd));
	if (type == '%')
		return (ft_putchar_fd('%', fd));
	return (0);
}

int	ft_fprintf(const int fd, const char *str, ...)
{
	int		i;
	va_list	ap;
	int		len;

	i = 0;
	va_start(ap, str);
	len = 0;
	if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
		return (0);
	if (str == NULL || fd < 0)
		return (0);
	while (str[i])
	{
		if (str[i] == '%')
		{
			len += convert(ap, str[i + 1], fd);
			i++;
		}
		else
			len += ft_putchar_fd(str[i], fd);
		i++;
	}
	va_end(ap);
	return (len);
}
