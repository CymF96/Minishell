/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofische <cofische@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:46:48 by cofische          #+#    #+#             */
/*   Updated: 2024/11/08 12:46:54 by cofische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>

bool	ft_char(char c, const char *str)
{
	while (*str)
	{
		if (*str++ != c)
			return (false);
	}
	return (true);
}
