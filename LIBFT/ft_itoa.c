/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:20:02 by mcoskune          #+#    #+#             */
/*   Updated: 2024/04/20 16:10:43 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_len(int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*p_mal;
	size_t	len;
	long	nb;

	nb = n;
	len = ft_len(n);
	p_mal = malloc(sizeof(char) * (len + 1));
	if (p_mal == 0)
		return (NULL);
	if (nb < 0)
	{
		p_mal[0] = '-';
		nb = -nb;
	}
	p_mal[len--] = '\0';
	if (nb == 0)
		p_mal[0] = '0';
	while (nb)
	{
		p_mal[len--] = nb % 10 + '0';
		nb /= 10;
	}
	return (p_mal);
}
