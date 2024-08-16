/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:43:14 by mcoskune          #+#    #+#             */
/*   Updated: 2024/08/15 11:43:06 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	clean_init_token_node(t_token *tkn)
{
	tkn->start_pos = -1;
	tkn->end_pos = -1;
	tkn->type = -1;
	tkn->token = NULL;
	tkn->prev = NULL;
	tkn->next = NULL;
}

void	clean_init_parse(t_parse *pars)
{
	pars->parsed_args = NULL;
	pars->head = NULL;
}

/*
----- CLEAN INITIALIZE -----
Function to set variables to their safe state. I.e. if a number is expected
to be positive, init to -1 otherwise to 0. If there is a pointer, all are
initialized to NULL. This is done to prevent derefencing an uninitialized func.
*/

void	clean_initialize(t_msh *msh)
{
	if (msh == NULL)
		exit_cleanup("Passed NULL to clean_init", NULL, errno);
	
	msh->input = NULL;
	msh->parse = NULL;
	msh->parent_str = NULL;
}