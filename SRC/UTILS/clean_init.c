/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofische <cofische@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:43:14 by mcoskune          #+#    #+#             */
/*   Updated: 2025/05/28 18:00:11 by cofische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

void	clean_init_chds(t_pipex *chds)
{
	chds->fd[0] = STDIN_FILENO;
	chds->fd[1] = STDOUT_FILENO;
	chds->pid = -1;
}

void	clean_init_pexe_node(t_pexe *pexe)
{
	pexe->type = TEMP;
	pexe->cmd = NULL;
	pexe->option = NULL;
	pexe->group_id = -1;
	pexe->p_index = -1;
	pexe->muk_note = REGULAR;
	pexe->temp = NULL;
	pexe->prev = NULL;
	pexe->next = NULL;
}

void	clean_init_token_node(t_token *tkn)
{
	tkn->token = NULL;
	tkn->start_pos = -1;
	tkn->end_pos = -1;
	tkn->type = REGULAR;
	tkn->prev = NULL;
	tkn->next = NULL;
}

void	clean_init_parse(t_parse *pars)
{
	pars->head = NULL;
	pars->modified = NULL;
	pars->no_poi = 0;
	pars->size_modified = 0;
	pars->poi = NULL;
	pars->here_fd = -1;
	pars->l_count = 0;
	pars->r_count = 0;
	pars->w_count = 0;
	pars->temp = NULL;
	pars->w_pos = NULL;
	pars->w_str = NULL;
}

void	clean_msh_init(t_msh *msh)
{
	msh->input = NULL;
	msh->path = NULL;
	msh->fd[0] = -1;
	msh->fd[1] = -1;
	msh->pipe_nb = 0;
	msh->flag = -1;
	msh->interrupted = 0;
	msh->parse = NULL;
	msh->pexe = NULL;
	msh->child = 0;
	msh->text = NULL;
	msh->heredoc = NULL;
	msh->hd_temp = NULL;
	msh->chds = NULL;
	msh->prompt_mode = 1;
	msh->hr_flag = 0;
}
