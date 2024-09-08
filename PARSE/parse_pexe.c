/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pexe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:24:14 by mcoskune          #+#    #+#             */
/*   Updated: 2024/09/08 17:37:38 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_pexe(t_pexe **pxe, t_pexe *ite, int *group, int *prio)
{
	while (*pxe != NULL && *pxe != ite)
	{
		if ((*pxe)->prev == NULL && (*pxe)->type != HEREDOC && (*pxe)->type != INFILE && (*pxe)->type != OUTFILE && (*pxe)->type != APPEND)
			(*pxe)->type = EXE;
		else if ((*pxe)->prev->prev == NULL && ((*pxe)->prev->type == HEREDOC || (*pxe)->prev->type == INFILE))
			(*pxe)->next->type = EXE;
		if ((*pxe)->muk_note == PIPE)
		{
			(*group)++;
			(*pxe)->type = EXE;
			(*pxe)->group_id = *group;
		}
		(*pxe)->group_id = *group;
		if ((*pxe)->type != HEREDOC && (*pxe)->type != INFILE && (*pxe)->type != OUTFILE && (*pxe)->type != APPEND)
		{
			// (*pxe)->cmd = (*pxe)->temp;
			(*pxe)->p_index = (*prio)++;
		}
		if ((*pxe)->type == TEMP || (*pxe)->type == REGULAR)
			(*pxe)->type = STRING;
		*pxe = (*pxe)->next;
	}
}

void	fill_pexe(t_msh *msh)
{
	t_pexe	*pxe;
	t_pexe	*ite;
	int		group;
	int		prio;

	pxe = msh->pexe;
	ite = pxe;
	group = 0;
	prio = 0;
	while (pxe != NULL)
	{
		ite = pxe->next;
		while (ite != NULL && ite->muk_note != PIPE)
		{
			if (ite->muk_note == HEREDOC || ite->muk_note == INFILE || ite->muk_note == OUTFILE || ite->muk_note == APPEND)
			{
				ite->type = ite->muk_note;
				// ite->cmd = ite->temp;
				ite->temp = NULL;
				ite->group_id = group;
				ite->p_index = prio;
				prio++;
			}
			ite = ite->next;
		}
		update_pexe(&pxe, ite, &group, &prio);
	}
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
		if (tkn_i->type != REGULAR)
		{
			node->muk_note = tkn_i->type;
			tkn_i = tkn_i->next;
		}
		node->temp = tkn_i->token;
		str = malloc(sizeof(char) * (ft_strlen(node->temp) + 1));
		remove_quotes(node->temp, -1, str);
		node->cmd = str;
		addnode((void *)node, (void **)&msh->pexe, offsetof(t_pexe, next), offsetof(t_pexe, prev));
		tkn_i = tkn_i->next;
	}
	fill_pexe(msh);
}
