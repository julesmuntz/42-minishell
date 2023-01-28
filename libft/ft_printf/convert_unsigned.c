/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_unsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 19:21:02 by julmuntz          #+#    #+#             */
/*   Updated: 2022/07/25 15:33:45 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	convert_unsigned(unsigned int decimal_u)
{
	unsigned int	len;

	len = ft_nbrlen_u(decimal_u);
	ft_putnbr_u(decimal_u);
	return (len);
}
