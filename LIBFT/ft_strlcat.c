/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 18:54:42 by mcoskune          #+#    #+#             */
/*   Updated: 2024/04/20 14:28:12 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	d_size;
	size_t	s_size;
	size_t	i;
	size_t	j;

	d_size = ft_strlen(dest);
	s_size = ft_strlen(src);
	if (size <= d_size)
		return (size + s_size);
	i = d_size;
	j = 0;
	while ((i + j) < (size - 1) && (src[j] != '\0'))
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (d_size + s_size);
}
