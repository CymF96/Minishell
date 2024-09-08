/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:32:51 by mcoskune          #+#    #+#             */
/*   Updated: 2024/09/08 15:50:49 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Checks if program is launched with correct number of parameters and
// if ENVP variable exists aka. not NULL
int	input_validate(int ac, char **envp)
{
	if (ac > 1)
	{
		exit_cleanup("Too many clowns for this party", NULL, errno, 2);
		return (-1);
	}
	else if (ac < 0)
	{
		exit_cleanup("How did you even manage neg AC?", NULL, errno, 2);
		return (-1);
	}
	if (envp == NULL || *envp == NULL)
	{
		exit_cleanup("Where is my ENVP!", NULL, errno, 2);
		return (-1);
	}
	return (0);
}
