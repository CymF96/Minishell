/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:43:14 by mcoskune          #+#    #+#             */
/*   Updated: 2024/08/23 10:12:15 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clean_init_pexe_node(t_pexe *pexe)
{
	pexe->type = -1;
	pexe->cmd = NULL;
	pexe->option = NULL;
	pexe->group_id = -1;
	pexe->p_index = -1;
	pexe->fd = NULL;
	pexe->prev = NULL;
	pexe->next = NULL;
}

void	clean_init_token_node(t_token *tkn)
{
	tkn->token = NULL;
	tkn->start_pos = -1;
	tkn->end_pos = -1;
	tkn->prev = NULL;
	tkn->next = NULL;
}

void	clean_init_parse(t_parse *pars)
{
	pars->modified = NULL;
	pars->size_modified = -1;
	pars->poi = NULL;
	pars->here_fd = -1;
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