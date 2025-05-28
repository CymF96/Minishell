/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:00:12 by mcoskune          #+#    #+#             */
/*   Updated: 2024/10/03 12:35:17 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_hex_size(unsigned long long n)
{
	int	size;

	size = 0;
	while (n != 0)
	{
		size++;
		n /= 16;
	}
	return (size);
}

static int	ft_hex_address(unsigned long long n)
{
	char	*base_16;
	int		size;

	size = ft_hex_size(n);
	base_16 = "0123456789abcdef";
	if (n == 0)
	{
		if (ft_printf_c('0') == -1)
			return (-1);
	}
	else if (n < 16)
	{
		if (ft_printf_c(base_16[n]) == -1)
			return (-1);
	}
	else
	{
		ft_hex_address(n / 16);
		ft_hex_address(n % 16);
	}
	return (size);
}

int	ft_printf_p(void *ptr)
{
	int	n;

	if (ptr == NULL)
	{
		if (ft_printf_s("(nil)") == -1)
			return (-1);
		return (5);
	}
	if (ft_printf_s("0x") == -1)
		return (-1);
	n = ft_hex_address((unsigned long long)ptr);
	return (n + 2);
}
