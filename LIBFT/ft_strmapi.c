/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:04:50 by mcoskune          #+#    #+#             */
/*   Updated: 2024/04/19 10:54:24 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*p_str;
	unsigned int	i;

	if (!s || (!s && !f))
		return (ft_strdup(""));
	if (!f)
		return (ft_strdup(s));
	p_str = ft_strdup(s);
	if (!p_str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		p_str[i] = (*f)(i, s[i]);
		i++;
	}
	return (p_str);
}
