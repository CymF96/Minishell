/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 16:44:34 by mcoskune          #+#    #+#             */
/*   Updated: 2024/05/09 17:50:01 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_parse(const char *fmt, size_t *i, va_list *pa)
{
	unsigned int	counter;

	counter = 0;
	if (fmt[*i] == 'c')
		counter += ft_printf_c (va_arg(*pa, int));
	else if (fmt[*i] == 's')
		counter += ft_printf_s(va_arg(*pa, char *));
	else if (fmt[*i] == 'p')
		counter += ft_printf_p(va_arg(*pa, void *));
	else if (fmt[*i] == 'd' || fmt[*i] == 'i')
		counter += ft_printf_di(va_arg(*pa, int));
	else if (fmt[*i] == 'x')
		counter += ft_printf_xx(va_arg(*pa, int), 0);
	else if (fmt[*i] == 'X')
		counter += ft_printf_xx(va_arg(*pa, int), 1);
	else if (fmt[*i] == 'u')
		counter += ft_printf_u(va_arg(*pa, int));
	else if (fmt[*i] == '%')
		counter += ft_printf_c('%');
	return (counter);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	pa;
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	va_start(pa, fmt);
	while (fmt[i] != '\0')
	{
		if (fmt[i] == '%')
		{
			i++;
			count += ft_parse(fmt, &i, &pa);
		}
		else
		{
			count += ft_printf_c(fmt[i]);
		}
		i++;
	}
	va_end(pa);
	return (count);
}
