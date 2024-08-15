/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 19:02:09 by mcoskune          #+#    #+#             */
/*   Updated: 2024/08/14 17:50:55 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_special_char(t_msh *msh)
{
	
}

void	parse_input(t_msh *msh)
{
	int	i;

	if (msh == NULL || msh->input == NULL || msh->input[0] == '\0')
		return ;
	i = 0;
	while (msh->input[i] != '\0')
	{
		
		


		i++;
	}

}