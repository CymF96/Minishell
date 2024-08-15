/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:00:44 by mcoskune          #+#    #+#             */
/*   Updated: 2024/05/09 17:50:17 by mcoskune         ###   ########.fr       */
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
		n /= 10;
		len++;
	}
	return (len);
}

static void	ft_putnbr(unsigned int nb)
{
	if (nb >= 10)
	{
		ft_putnbr(nb / 10);
		ft_putchar_fd((nb % 10) + '0', 1);
	}
	else
		ft_putchar_fd(nb + '0', 1);
}

int	ft_printf_u(unsigned int nb)
{
	size_t	counter;

	counter = ft_len(nb);
	ft_putnbr(nb);
	return (counter);
}
