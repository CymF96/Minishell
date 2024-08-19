/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:01:50 by mcoskune          #+#    #+#             */
/*   Updated: 2024/08/19 19:18:05 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"




int	parse_main(t_msh *msh)
{
	t_parse	*pars;
	
	if (msh == NULL || msh->input == NULL || msh->input[0] == '\0')
		return (1);
	parse_malloc(msh, pars);
	parse_tokenize(msh, pars);
	initial_expansion(msh, pars);
	return (0);
}