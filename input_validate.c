/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:32:51 by mcoskune          #+#    #+#             */
/*   Updated: 2024/08/13 17:45:00 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_validate(int ac, char **envp)
{
	if (ac != 1)
		exit_cleanup("Too many clowns for this party", NULL, errno);
	if (envp == NULL || *envp == NULL)
		exit_cleanup("Where is my ENVP!", NULL, errno);
}
