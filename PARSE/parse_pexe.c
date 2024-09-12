/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pexe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:24:14 by mcoskune          #+#    #+#             */
/*   Updated: 2024/09/12 12:56:55 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	remove_node(t_pexe *node)
{
	t_pexe	*temp;

	free(node->cmd);
	temp = node->prev;
	temp->next = node->next;
	temp = node->next;
	temp->prev = node->prev;
	free(node);
}

static void	handle_groups(t_pexe *init, int *group)
{
	t_pexe	*temp;

	temp = init;
	while (temp != NULL)
	{
		if (temp->muk_note == PIPE)
			(*group)++;
		temp->group_id = *group;
		temp = temp->next;
		if (temp != NULL && temp->prev->muk_note == PIPE)
			remove_node(temp->prev);
	}
}

static void	find_ex(t_pexe *init, t_pexe *ite, int *prio)
{
	t_pexe	*temp;

	temp = init;
	while (temp != ite)
	{
		if (temp->type == TEMP)
		{
			temp->type = EXE;
			temp->cmd = temp->temp;
			temp->p_index = (*prio)++;
			return ;
		}
	}
}

static void	move_init(t_pexe *init, t_pexe *ite, int *prio, int *zone)
{
	while (init != ite)
	{
		init->type = STRING;
		init->cmd = init->temp;
		init->p_index = (*prio)++;
		init = init->next;
	}
	if (init == NULL)
		*zone = -1;
	else
		(*zone)++;
}

static void	handle_docs(t_pexe *init, t_pexe *ite, int *prio)
{
	int	zone;

	zone = 0;
	while (zone != -1)
	{
		while (ite != NULL && ite->group_id == zone)
		{
			if (ite->muk_note == HEREDOC || ite->muk_note == INFILE || \
				ite->muk_note == OUTFILE || ite->muk_note == APPEND)
			{
				ite = ite->next;
				ite->type = ite->prev->type;
				remove_node(ite->prev);
				if (ite->type == OUTFILE || ite->type == APPEND)
					ite->p_index = (*prio)++;
			}
			ite = ite->next;
		}
		find_ex(init, ite, prio);
		move_init(init, ite, prio, &zone);
	}
}

void	fill_pexe(t_msh *msh)
{
	t_pexe	*ite;
	t_pexe	*init;
	int		prio;
	int		group;

	prio = 0;
	group = 0;
	ite = msh->pexe;
	init = ite;
	handle_groups(init, &group);
	handle_docs(init, ite, &prio);
}

void	make_pexe(t_msh *msh, t_parse *pars)
{
	t_pexe	*node;
	t_token	*tkn_i;
	char	*str;

	tkn_i = pars->head;
	while (tkn_i != NULL)
	{
		node = pexe_malloc(msh);
		node->muk_note = tkn_i->type;
		node->temp = tkn_i->token;
		str = ft_strdup(tkn_i->token);
		node->cmd = str;
		addnode((void *)node, (void **)&msh->pexe, offsetof(t_pexe, next), \
			offsetof(t_pexe, prev));
		tkn_i = tkn_i->next;
	}
	fill_pexe(msh);
}
