/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 16:44:45 by mcoskune          #+#    #+#             */
/*   Updated: 2024/07/11 13:30:52 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include "libft.h"

int	ft_printf_c(int c);
int	ft_printf_s(char *s);
int	ft_printf_p(void *ptr);
int	ft_printf(const char *fmt, ...);
int	ft_printf_di(int n);
int	ft_printf_xx(unsigned int n, int x_switch);
int	ft_printf_u(unsigned int n);

#endif