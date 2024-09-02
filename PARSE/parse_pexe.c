/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pexe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:42:32 by mcoskune          #+#    #+#             */
/*   Updated: 2024/09/02 18:14:33 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void handle_files(t_pexe *ite, int *prio)
{
	t_pexe	*temp;

	temp = ite;
	while (temp != NULL)
	{
		if (temp->muk_note == INFILE || temp->muk_note == HEREDOC || \
			temp->muk_note == OUTFILE || temp->muk_note == APPEND)
		{
			temp->type = temp->muk_note;
			temp->cmd = temp->temp;
			temp->p_index = *prio;
			(*prio)++;
		}
		temp = temp->next;
	}
}

void	fill_pexe(t_pexe *pexe) //t_token *token parameter
{
	int	prio;
	int	group;
	t_pexe	*ite;
	int		flag;

	prio = 0;
	group = 0;
	ite = pexe;
	flag = 0;
	handle_files(ite, &prio);
	while (ite != NULL)
	{
		if ((int)ite->type == -1 && (int)ite->muk_note == 0)
		{
			if (flag == 0)
			{
				ite->type = EXE;
				ite->cmd = ite->temp;
				ite->option[0] = ite->temp;
				flag++;
				ite->group_id = group;
				
			}
			else if(flag == 1)
			{
				ite->type = STRING;
				ite->cmd = ite->temp;
				ite->group_id = group;
				ite->p_index = prio++;
			}
		}
		else if (ite->muk_note == PIPE)
		{
			group++;
			ite->type = EXE;
			ite->group_id = group;
			ite->p_index = prio++;
		}
		ite = ite->next;
	}
}

// Iterates through the token list and creates the pexe structure
void	make_pexe(t_msh *msh, t_parse *pars)
{
	t_pexe	*temp;
	t_token	*list;

	list = pars->head;
	while (list != NULL)
	{
		temp = pexe_malloc(msh); //pars parameter
		temp->muk_note = check_special(list->token, 0); //temp parameter
		if ((int)temp->muk_note != 0)
			list = list->next;
		temp->temp = list->token;
		addnode(temp, (void**)msh->pexe, offsetof(t_pexe, next), offsetof(t_pexe, prev));
		list = list->next;
	}
	fill_pexe(msh->pexe);
}
