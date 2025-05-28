/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 13:17:12 by mcoskune          #+#    #+#             */
/*   Updated: 2024/04/13 18:48:58 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*p1;
	const char	*p2;

	if (!dest || !src || n == 0)
		return (dest);
	p1 = (char *)dest;
	p2 = (const char *)src;
	if (p2 > p1)
		while (n-- > 0)
			*p1++ = *p2++;
	else
	{
		p1 += n - 1;
		p2 += n - 1;
		while (n-- > 0)
			*p1-- = *p2--;
	}
	return (dest);
}
