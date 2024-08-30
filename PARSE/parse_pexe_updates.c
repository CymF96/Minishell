/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pexe_updates.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:38:38 by mcoskune          #+#    #+#             */
/*   Updated: 2024/08/30 12:51:37 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void update_rest(t_pexe *pexe)
{
	t_pexe	*temp;
	int		count;

	count = 0;
	temp = pexe;
	while (temp != NULL)
	{
		if (count == 0 && temp->type == -1)
		{
			temp->type = EXE;
			temp->cmd = 
		}
	}
}

static void	update_file(t_pexe *pexe)
{
	t_pexe	*temp;

	temp = pexe;
	while (temp != NULL)
	{
		if (temp->muk_note == INFILE || temp->muk_note == OUTFILE || \
			temp->muk_note == APPEND || temp->muk_note == HEREDOC)
		{
			temp->type = temp->muk_note;
			temp->cmd = temp->temp;
			temp->temp = NULL;
			if (temp->muk_note != HEREDOC)
				temp->p_index = 0;
		}
		temp = temp ->next;
	}
}

void	update_pexe_main(t_msh *msh, t_pexe *pexe)
{
	update_file(pexe);
	update_rest(pexe);
	check_for_flags();
	rearrange_nodes(pexe);

}