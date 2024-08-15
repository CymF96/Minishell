/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:26:58 by mcoskune          #+#    #+#             */
/*   Updated: 2024/04/20 15:13:07 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*p_last;
	unsigned char	ch;
	size_t			i;

	i = ft_strlen(s);
	p_last = (char *)s + i;
	ch = (unsigned char)c;
	if (ch == '\0')
		return (p_last++);
	while (p_last >= s)
	{
		if (*p_last == ch)
			return (p_last);
		p_last--;
	}
	p_last = NULL;
	return (p_last);
}
