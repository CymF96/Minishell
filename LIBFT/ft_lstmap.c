/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:41:07 by mcoskune          #+#    #+#             */
/*   Updated: 2024/04/21 10:03:32 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*current;

	if (!lst)
		return (NULL);
	newlst = NULL;
	current = NULL;
	while (lst)
	{
		if (!f)
			current = ft_lstnew(lst->content);
		else
			current = ft_lstnew(f(lst->content));
		if (!current)
		{
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		ft_lstadd_back(&newlst, current);
		lst = lst->next;
	}
	return (newlst);
}
