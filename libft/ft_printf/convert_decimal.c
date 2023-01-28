/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_decimal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 15:19:36 by julmuntz          #+#    #+#             */
/*   Updated: 2022/07/25 15:33:45 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	convert_decimal(int decimal)
{
	int	len;

	if (decimal == INT_MIN)
		return (write(1, "-2147483648", 11));
	len = ft_nbrlen(decimal);
	ft_putnbr(decimal);
	return (len);
}
