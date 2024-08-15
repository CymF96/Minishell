/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:58:53 by mcoskune          #+#    #+#             */
/*   Updated: 2024/04/20 13:31:45 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*p_dest;
	const char	*p_src;

	if (!dest || !src || n == 0 || (dest == src))
		return (dest);
	p_dest = (char *)dest;
	p_src = (const char *)src;
	while (n != 0)
	{
		*p_dest++ = *p_src++;
		n--;
	}
	return (dest);
}
