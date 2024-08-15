/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:31:41 by mcoskune          #+#    #+#             */
/*   Updated: 2024/04/14 16:38:24 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*p_s;
	unsigned char		ch;

	ch = (unsigned char)c;
	p_s = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (p_s[i] == ch)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}
