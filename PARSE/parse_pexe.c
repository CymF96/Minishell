/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pexe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:24:14 by mcoskune          #+#    #+#             */
/*   Updated: 2024/09/12 18:07:44 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static void	remove_node(t_msh *msh, t_pexe **node)
// {
// 	t_pexe	*temp;

// 	if ((*node)->cmd != NULL)
// 		free((*node)->cmd);
// 	if ((*node)->temp != NULL)
// 		free((*node)->temp);
// 	if ((*node)->prev != NULL)
// 	{
// 		temp = (*node)->prev;
// 		temp->next = (*node)->next;
// 		temp = (*node)->next;
// 		temp->prev = (*node)->prev;
// 	}
// 	else if ((*node)->prev == NULL)
// 	{
// 		msh->pexe = (*node)->next;
// 		(*node)->next->prev = NULL;
// 	}
// 	free(*node); // check as temp prev becomes NULL after freeing node
// 	*node = NULL;
// }

// static void	find_ex(t_msh *msh, t_pexe *init, t_pexe *ite, int *prio)
// {
// 	t_pexe	*temp;

// 	temp = init;
// 	while (temp != NULL && (temp != ite || ite == msh->pexe))// check when only one node like "echo"
// 	{
// 		if (temp->type == TEMP)
// 		{
// 			temp->type = EXE;
// 			// temp->cmd = ft_strdup(temp->temp);
// 			temp->p_index = (*prio)++;
// 			return ;
// 		}
// 		if (temp != NULL && temp->next != NULL)
// 			temp = temp->next;
// 	}
// }

// static void	move_init(t_pexe **init, t_pexe **ite, int *prio, int *zone)
// {
// 	while (*init != *ite)
// 	{
// 		if ((*init)->type == TEMP)
// 			(*init)->type = STRING;
// 		(*init)->cmd = ft_strdup((*init)->temp); // leak to check when already malloc command (ex, cat)
// 		if ((*init)->p_index == -1)
// 			(*init)->p_index = (*prio)++;
// 		*init = (*init)->next;
// 	}
// 	if ((*init) == NULL)
// 		*zone = -1;
// 	else
// 		(*zone)++;
// }

// static void	handle_docs(t_msh *msh, t_pexe **init, t_pexe **ite, int *prio)
// {
// 	int	zone;

// 	zone = 0;
// 	while (zone != -1)
// 	{
// 		while (*ite != NULL && (*ite)->group_id == zone)
// 		{
// 			if ((*ite)->muk_note == HEREDOC || (*ite)->muk_note == INFILE || \
// 				(*ite)->muk_note == OUTFILE || (*ite)->muk_note == APPEND)
// 			{
// 				*ite = (*ite)->next;
// 				(*ite)->type = (*ite)->prev->muk_note;
// 				if (*init == (*ite)->prev)
// 					*init = (*init)->next;
// 				remove_node(msh, &(*ite)->prev);
// 				if ((*ite)->type == OUTFILE || (*ite)->type == APPEND)
// 					(*ite)->p_index = (*prio)++;
// 			}
// 			*ite = (*ite)->next;
// 		}
// 		find_ex(msh, *init, *ite, prio);
// 		move_init(init, ite, prio, &zone);
// 	}
// }

// static void	handle_groups(t_msh *msh, t_pexe **init, int *group)
// {
// 	while (*init != NULL)
// 	{
// 		if ((*init)->muk_note == PIPE)
// 			(*group)++;
// 		(*init)->group_id = *group;
// 		(*init) = (*init)->next;
// 		if ((*init) != NULL && (*init)->prev != NULL && (*init)->prev->muk_note == PIPE)
// 			remove_node(msh, &(*init)->prev);
// 	}
// }

// void	fill_pexe(t_msh *msh)
// {
// 	t_pexe	*ite;
// 	t_pexe	*init;
// 	int		prio;
// 	int		group;

// 	prio = 0;
// 	group = 0;
// 	ite = msh->pexe;
// 	init = ite;
// 	handle_groups(msh, &init, &group);
// 	init = ite;
// 	handle_docs(msh, &init, &ite, &prio);
// }

void	make_pexe(t_msh *msh, t_parse *pars)
{
	t_pexe	*node;
	t_token	*tkn_i;

	tkn_i = pars->head;
	while (tkn_i != NULL)
	{
		node = pexe_malloc(msh);
		node->muk_note = tkn_i->type;
		node->temp = ft_strdup(tkn_i->token);
		addnode((void *)node, (void **)&msh->pexe, offsetof(t_pexe, next), \
			offsetof(t_pexe, prev));
		tkn_i = tkn_i->next;
	}
	fill_pexe(msh);
}
