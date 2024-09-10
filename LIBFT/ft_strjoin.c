/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 19:22:24 by mcoskune          #+#    #+#             */
/*   Updated: 2024/09/03 11:47:47 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p_mal;
	size_t	len;
	int		i;
	int		j;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	p_mal = ft_calloc(len, sizeof(char));
	if (!p_mal)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0' && s1[i] != '\n')
	{
		p_mal[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0' && s2[j] != '\n')
	{
		p_mal[i + j] = s2[j];
		j++;
	}
	p_mal[i + j] = '\0';
	return (p_mal);
}
