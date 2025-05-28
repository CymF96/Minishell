/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:43:16 by mcoskune          #+#    #+#             */
/*   Updated: 2024/04/24 14:05:21 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	little_len;

	if (*little == '\0')
		return ((char *)big);
	if (big == NULL || len == 0)
		return (NULL);
	little_len = ft_strlen(little);
	i = 0;
	while (i < len && big[i] != '\0')
	{
		j = 0;
		while (i + j < len && big[i + j] != '\0' && \
			little[j] != '\0' && big[i + j] == little[j])
		{
			j++;
		}
		if (j == little_len)
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
