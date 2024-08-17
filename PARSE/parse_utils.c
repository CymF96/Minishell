/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:24:04 by mcoskune          #+#    #+#             */
/*   Updated: 2024/08/16 11:38:21 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	make_token(t_msh *msh, t_token *tkn)
{
	tkn->token = malloc (sizeof(char) * (tkn->end_pos - tkn->start_pos + 2));
	if (tkn->token == NULL)
		exit_cleanup("Malloc Failed", msh, errno);
	ft_strlcpy(tkn->token, msh->input + tkn->start_pos, \
		tkn->end_pos - tkn->start_pos + 1);
	tkn->token[tkn->end_pos - tkn->start_pos + 2] = '\0';
}

void	add_token_node(t_parse *pars, t_token *tkn)
{
	t_token	*temp;

	if (tkn->type == SPACE)
		return ;
	temp = pars->head;
	if (temp != NULL)
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = tkn;
		tkn->prev = temp;
	}
	else if (temp == NULL)
		pars->head = tkn;
}

t_token	*token_structure_malloc(t_msh *msh)
{
	t_token	*tkn;

	tkn = malloc(sizeof(t_token));
	if (tkn == NULL)
		exit_cleanup("Malloc Failed", msh, errno);
	clean_init_token_node(tkn);
	return (tkn);
}

void	parse_structure_malloc(t_msh *msh)
{
	t_parse	*pars;

	pars = malloc(sizeof(t_parse));
	if (pars == NULL)
		exit_cleanup("Malloc Failed", msh, errno);
	clean_init_parse(pars);
	msh->parse = pars;
}
