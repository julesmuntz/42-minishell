/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_hex_upper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 19:48:20 by julmuntz          #+#    #+#             */
/*   Updated: 2022/07/25 15:33:45 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	convert_hex_upper(unsigned int hex_upper)
{
	unsigned int	len;

	len = ft_hexlen_u(hex_upper);
	ft_puthex_u_upper(hex_upper);
	return (len);
}
