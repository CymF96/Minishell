/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pexe_cleaner.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 20:09:22 by mcoskune          #+#    #+#             */
/*   Updated: 2024/10/14 22:46:08 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// If single quote, prints all as char. In double quote checks for $ and expands
int	handle_quote(t_msh *msh, int *i)
{
	int	start;
	int	flag;

	flag = 0;
	start = (*i)++;
	if (msh->input[(*i) - 1] == '\'')
	{
		while (msh->input[*i] != '\'' && msh->input[*i] != '\0')
			(*i)++;
		copy_input_mod(msh, &msh->input[start], start, (*i));
	}
	else if (msh->input[(*i) - 1] == '\"')
	{
		if (handle_dquote(msh, i, &start, &flag) == 1)
			return (1);
	}
	(*i)++;
	return (0);
}

static void	remove_helper(t_msh *msh, t_pexe **ite, t_pexe **temp)
{
	if (*ite == msh->pexe)
	{
		*ite = (*ite)->next;
		(*ite)->prev = NULL;
		msh->pexe->next = NULL;
		free_pexe(msh);
		msh->pexe = *ite;
	}
	else
	{
		(*ite)->prev->next = (*ite)->next;
		(*ite)->next->prev = (*ite)->prev;
		*temp = (*ite)->next;
		free((*ite)->cmd);
		free(*ite);
		*ite = *temp;
		*temp = NULL;
	}
	*ite = (*ite)->next;
}

void	remove_nodes(t_msh *msh)
{
	t_pexe	*ite;
	t_pexe	*temp;

	ite = msh->pexe;
	temp = NULL;
	while (ite != NULL)
	{
		if (ite->p_index == -2)
			remove_helper(msh, &ite, &temp);
		else
			ite = ite->next;
	}
}
