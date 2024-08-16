/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:00:13 by mcoskune          #+#    #+#             */
/*   Updated: 2024/08/13 18:34:36 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_cleanup(char *msg, t_msh *msh, int flag)
{
	if (flag != 0)
		printf("Error\n");
	if (msg != NULL)
		printf("Program Termination Reason - %s\n", msg);
	if (msh != NULL)
	{
		free(msh->input);
		msh->input = NULL;
	}
	rl_clear_history();

	exit(flag);
}
