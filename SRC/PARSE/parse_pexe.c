/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pexe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofische <cofische@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:24:14 by mcoskune          #+#    #+#             */
/*   Updated: 2025/05/28 17:59:52 by cofische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

static void	find_ex(t_pexe **front, t_pexe **back, int *prio)
{
	t_pexe	*temp;

	temp = *back;
	while (temp != NULL && temp != *front)
	{
		if (temp->type == INFILE || temp->type == OUTFILE || \
		temp->type == HEREDOC || temp->type == APPEND || temp->type == DOLLAR)
		{
			temp = temp->next;
		}
		else if (temp->type == REGULAR || temp->type == TEMP)
		{
			temp->type = EXE;
			temp->p_index = (*prio)++;
			break ;
		}
	}
	while (*back != *front)
	{
		if ((*back)->p_index == -1)
			(*back)->p_index = (*prio)++;
		if ((*back)->type == TEMP)
			(*back)->type = STRING;
		(*back) = (*back)->next;
	}
}

static void	fill_x_range(t_pexe **front, t_pexe **back, int *prio)
{
	t_pexe	*temp;

	temp = *back;
	while (temp != NULL && temp != *front)
	{
		if (temp->muk_note == OUTFILE || temp->muk_note == APPEND)
		{
			temp->type = DOLLAR;
			temp->p_index = -2;
			temp->next->type = temp->muk_note;
			temp = temp->next;
			temp->cmd = temp->temp;
			temp->p_index = (*prio)++;
		}
		else if (temp->muk_note == INFILE || temp->muk_note == HEREDOC)
		{
			temp->type = DOLLAR;
			temp->p_index = -2;
			temp->next->type = temp->muk_note;
			temp = temp->next;
			temp->cmd = temp->temp;
		}
		temp = temp->next;
	}
	find_ex(front, back, prio);
}

static void	fill_pexe(t_msh *msh)
{
	int		prio;
	t_pexe	*front;
	t_pexe	*back;

	prio = 0;
	front = msh->pexe;
	back = msh->pexe;
	while (front != NULL)
	{
		if (front->muk_note == PIPE)
		{
			front->type = DOLLAR;
			front->p_index = -2;
			fill_x_range(&front, &back, &prio);
		}
		front->cmd = front->temp;
		front = front->next;
	}
	if (front != back)
		fill_x_range(&front, &back, &prio);
	remove_nodes(msh);
	remove_nodes(msh);
}

void	make_pexe(t_msh *msh, t_parse *pars)
{
	t_pexe	*node;
	t_token	*tkn_i;
	int		group;

	group = 0;
	tkn_i = pars->head;
	while (tkn_i != NULL)
	{
		node = pexe_malloc(msh);
		if (tkn_i->type == PIPE)
			group++;
		node->group_id = group;
		node->muk_note = tkn_i->type;
		node->temp = ft_strdup(tkn_i->token);
		addnode((void *)node, (void **)&msh->pexe, offsetof(t_pexe, next), \
			offsetof(t_pexe, prev));
		tkn_i = tkn_i->next;
	}
	fill_pexe(msh);
}
