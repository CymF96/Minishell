/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_xx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:59:09 by mcoskune          #+#    #+#             */
/*   Updated: 2024/05/01 11:06:51 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_len(unsigned int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n /= 16;
		len++;
	}
	return (len);
}

int	ft_printf_xx(unsigned int n, int x_case)
{
	char	*hex_base;
	size_t	len;

	len = ft_len(n);
	hex_base = "0123456789abcdef";
	if (x_case == 1)
		hex_base = "0123456789ABCDEF";
	if (n < 16)
	{
		if (ft_printf_c(hex_base[n]) == -1)
			return (-1);
	}
	else
	{
		if (ft_printf_xx(n / 16, x_case) == -1)
			return (-1);
		if (ft_printf_xx(n % 16, x_case) == -1)
			return (-1);
	}
	return (len);
}
