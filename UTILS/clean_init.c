/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:43:14 by mcoskune          #+#    #+#             */
/*   Updated: 2024/08/19 18:22:12 by mcoskune         ###   ########.fr       */
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
	// pexe->type = -1;
	pexe->cmd = NULL;
	pexe->option = NULL;
	pexe->group_id = -1;
	pexe->p_index = -1;
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
	pars->modified = NULL;
	pars->size_modified = -1;
	pars->poi = NULL;
	pars->here_fd = -1;
}

void	clean_msh_init(t_msh *msh)
{
	msh->input =  NULL;
	msh->envp = NULL;
	msh->fd[0] = STDIN_FILENO;
	msh->fd[1] = STDOUT_FILENO;
	msh->pipe_nb = 0;
	msh->flag = -1;
	msh->parse = NULL;
	msh->pipe_nb = 0;
	msh->pexe = NULL; 
	msh->main_child = -1;
	msh->signal_flags = 0;
}
