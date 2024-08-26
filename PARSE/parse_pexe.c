/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pexe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:42:32 by mcoskune          #+#    #+#             */
/*   Updated: 2024/08/26 18:57:09 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_type	check_special(t_token *tkn, t_pexe *temp)
{
	if (tkn->type == IO_I)
		return (INFILE);
	else if (tkn->type == HEREDC)
		return (HEREDOC);
	else if (tkn->type == IO_O)
		return (OUTFILE);
	else if (tkn->type == APPND)
		return (APPEND);
	else if (tkn->type == PIPE)
		return (PIPE);
	else if (tkn->type == W_C)
		return (WILDCARD);
}

static int	fill_pexe(t_pexe *pexe, t_token *token, int *count)
{
	if (*count == 0)
	{
		pexe->type = EXE;
		pexe->cmd = token->token;
		pexe->option[0] = token->token;
	}
	else if (pexe->type != -1)
	{
		/* code */
	}
	
}

// Iterates through the token list and creates the pexe structure
void	make_pexe(t_msh *msh, t_parse *pars)
{
	t_pexe	*temp;
	t_token	*list;
	int		count;

	list = pars->head;
	count = 0;
	while (list != NULL)
	{
		temp = pexe_malloc(msh, pars);
		temp->type = check_special(list, temp);
		if (temp->type == HEREDOC || temp->type == INFILE || \
				temp->type == OUTFILE || temp->type == APPEND)
		{
			list = list->next;
			temp->cmd = list->token;
		}
		else
		{
			fill_pexe(temp, list, &count);
			count++;
		}
		add_node((void **)&msh->pexe, (void *)temp, \
				FIELD_OFFSET(t_pexe, next), FIELD_OFFSET(t_pexe, prev));
		list = list->next;
	}
}
