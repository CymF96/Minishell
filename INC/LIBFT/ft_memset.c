/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:32:51 by mcoskune          #+#    #+#             */
/*   Updated: 2024/04/20 13:17:47 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	i;
	unsigned char	*p;

	if (!s)
		return (NULL);
	p = (unsigned char *)s;
	i = (unsigned char)c;
	while (n--)
	{
		*p++ = i;
	}
	return (s);
}
