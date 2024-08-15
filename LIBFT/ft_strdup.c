/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 09:04:57 by mcoskune          #+#    #+#             */
/*   Updated: 2024/04/14 17:58:28 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	size_t	len;
	char	*ptr;

	len = ft_strlen(src) + 1;
	ptr = malloc (len * sizeof(char));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, src, len);
	return (ptr);
}
