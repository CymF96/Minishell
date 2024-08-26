/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_make_pexe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:42:32 by mcoskune          #+#    #+#             */
/*   Updated: 2024/08/22 18:18:20 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	make_pexe(t_msh *msh, t_parse *pars)
{
	t_pexe	*temp;
	t_token	*list;

	list = pars->head;
	while (list != NULL)
	{
		temp = pexe_malloc(msh, pars);
		


		add_node((void **)&msh->pexe, (void *)temp, \
			FIELD_OFFSET(t_pexe, next), FIELD_OFFSET(t_pexe, prev));
	}
}