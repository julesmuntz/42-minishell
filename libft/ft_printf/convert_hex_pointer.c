/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_hex_pointer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:56:12 by julmuntz          #+#    #+#             */
/*   Updated: 2022/07/25 15:33:45 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	convert_hex_pointer(unsigned long int hex_pointer)
{
	unsigned long int	len;

	len = ft_hexlen_ul(hex_pointer);
	if (hex_pointer)
		write(1, "0x", 2);
	else
		return (write(1, "(nil)", 5));
	ft_puthex_ul(hex_pointer);
	return (len + 2);
}
