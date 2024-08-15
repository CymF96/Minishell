/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:03:05 by mcoskune          #+#    #+#             */
/*   Updated: 2024/04/20 15:20:35 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t		i;
	const char	*p1;
	const char	*p2;

	if (n <= 0)
		return (0);
	p1 = (const char *)s1;
	p2 = (const char *)s2;
	i = 0;
	while ((i < n - 1) && (p1[i] == p2[i]))
		i++;
	return ((unsigned char)p1[i] - (unsigned char)p2[i]);
}
