/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pexe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:24:14 by mcoskune          #+#    #+#             */
/*   Updated: 2024/09/03 18:03:22 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	pexe_upt_prio(t_msh *msh)
{
	int		prio;
	t_pexe	*temp;

	prio = 0;
	temp = msh->pexe;
	if (temp == NULL)
		return ;
	while (temp != NULL)
	{
		temp->p_index = prio;
		prio++;
		temp = temp->next;
	}
}

static void	pexe_upt_group(t_msh *msh)
{
	int		group;
	t_pexe	*temp;

	group = 0;
	temp = msh->pexe;
	if (temp == NULL)
		return ;
	while (temp != NULL)
	{
		if (temp->muk_note == PIPE)
			group++;
		temp->group_id = group;
		temp = temp->next;
	}
}

void	fill_pexe(t_pexe *node)
{
	if (node->muk_note == HEREDOC || node->muk_note == INFILE || node->muk_note == APPEND || node->muk_note == OUTFILE)
	{
		node->type = node->muk_note;
		node->cmd = node->temp;
		node->p_index = 0;
		node->temp = NULL;
	}
	else if (node->muk_note == STRING || node->muk_note == REGULAR)
	{
		if (node->prev == NULL || node->prev->type!= EXE)
			node->type = EXE;
		else
			node->type = STRING;
		node->cmd = node->temp;
		node->temp = NULL;
	}
	else if (node->muk_note == PIPE)
	{
		node->type = EXE;
		node->cmd = node->temp;
		node->temp = NULL;
	}
	node->option = malloc (sizeof(char *) * 3);
	node->option[0] = ft_strdup("echo");
	node->option[1] = ft_strdup("Hello");
	node->option[2] = NULL;
}

void	make_pexe(t_msh *msh, t_parse *pars)
{
	t_pexe	*node;
	t_token	*tkn_i;

	tkn_i = pars->head;
	while (tkn_i != NULL)
	{
		node = pexe_malloc(msh);
		if (tkn_i->type != REGULAR)
		{
			node->muk_note = tkn_i->type;
			node->temp = tkn_i->token;
			tkn_i = tkn_i->next;
		}
		fill_pexe(node);
		addnode((void *)node, (void **)&msh->pexe, offsetof(t_pexe, next), offsetof(t_pexe, prev));
		tkn_i = tkn_i->next;
	}
	pexe_upt_group(msh);
	pexe_upt_prio(msh);
}
