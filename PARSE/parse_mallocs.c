/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mallocs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:24:52 by mcoskune          #+#    #+#             */
/*   Updated: 2024/09/02 10:26:12 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_pexe	*pexe_malloc(t_msh *msh)
{
	t_pexe	*temp;
	int		i;

	i = 0;
	temp = malloc(sizeof(t_pexe));
	if (temp == NULL)
		exit_cleanup("Malloc Failed", msh, errno, 2);
	clean_init_pexe_node(temp);
	temp->option = malloc(sizeof(char *) * 4);
	if (temp->option == NULL)
		exit_cleanup("Malloc failed", msh, errno, 2);
	while (i < 4)
		temp->option[i++] = NULL;
	return (temp);
}

t_token	*token_malloc(t_msh *msh)
{
	t_token	*tkn;

	tkn = malloc(sizeof(t_token));
	if (tkn == NULL)
		exit_cleanup("Malloc Failed", msh, errno, 2);
	clean_init_token_node(tkn);
	return (tkn);
}

void	parse_malloc(t_msh *msh)
{
	t_parse	*prs;

	prs = malloc(sizeof(t_parse));
	if (prs == NULL)
		exit_cleanup("Malloc Failed", msh, errno, 2);
	clean_init_parse(prs);
	msh->parse = prs;
}