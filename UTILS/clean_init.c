/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:43:14 by mcoskune          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/08/26 17:35:05 by mcoskune         ###   ########.fr       */
=======
/*   Updated: 2024/08/19 18:22:12 by mcoskune         ###   ########.fr       */
>>>>>>> bc775e16d2e769939c25b04bf7d5784a4a751299
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clean_init_chds(t_pipex *chds)
{
	chds->fd[0] = STDIN_FILENO;
	chds->fd[1] = STDOUT_FILENO;
	chds->pid = -1;
}

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
	tkn->type = -1;
	tkn->prev = NULL;
	tkn->next = NULL;
}

void	clean_init_parse(t_parse *pars)
{
	
	pars->head = NULL;
}

/*
----- CLEAN INITIALIZE -----
Function to set variables to their safe state. I.e. if a number is expected
to be positive, init to -1 otherwise to 0. If there is a pointer, all are
initialized to NULL. This is done to prevent derefencing an uninitialized func.
*/
void	clean_msh_init(t_msh *msh)
{
	msh->input =  NULL;
	msh->envp = NULL;
	msh->fd[0] = STDIN_FILENO;
	msh->fd[1] = STDOUT_FILENO;
	msh->pipe_nb = 0;
	msh->flag = -1;
	msh->exit_error = -1;
	msh->parse = NULL;
<<<<<<< HEAD
	msh->pipe_nb = 0;
	// msh->parent_str = NULL;
}
=======
	msh->pexe = NULL; 
	msh->main_child = -1;	
}

// void	clean_initialize(t_msh *msh) //double with the clean_msh_init function 
// {
// 	if (msh == NULL)
// 		exit_cleanup("Passed NULL to clean_init", NULL, errno);
// 	msh->input = NULL; 
// 	msh->parse = NULL;
// }
>>>>>>> bc775e16d2e769939c25b04bf7d5784a4a751299
