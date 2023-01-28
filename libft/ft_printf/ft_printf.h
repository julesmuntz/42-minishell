/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:13:21 by julmuntz          #+#    #+#             */
/*   Updated: 2022/09/29 15:08:07 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft.h"

int	ft_printf(const char *str, ...);
int	convert_char(char c);
int	convert_string(char *s);
int	convert_hex_pointer(unsigned long int hex_pointer);
int	convert_decimal(int decimal);
int	convert_integer(int integer);
int	convert_unsigned(unsigned int decimal_u);
int	convert_hex_lower(unsigned int hex_lower);
int	convert_hex_upper(unsigned int hex_upper);

#endif