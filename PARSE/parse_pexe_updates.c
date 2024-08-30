/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pexe_updates.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:38:38 by mcoskune          #+#    #+#             */
/*   Updated: 2024/08/30 11:31:47 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

update_files(t_pexe *pexe)
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
		}
		temp = temp ->next;
	}
}

void	update_pexe_main(t_msh *msh, t_pexe *pexe)
{



	update_file(pexe);

}