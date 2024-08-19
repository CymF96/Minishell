/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mallocs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:24:52 by mcoskune          #+#    #+#             */
/*   Updated: 2024/08/19 20:10:36 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_node(void **head, void *node, size_t next_off, size_t prev_off)
{
	void	**new_node_next;
	void	**new_node_prev;
	void	**current_next;

	if (*head == NULL)
	{
		*head = node;
		new_node_next = (void **)((char *)node + next_off);
		new_node_prev = (void **)((char *)node + prev_off);
		*new_node_next = NULL;
		*new_node_prev = NULL;
	}
	else
	{
		current_next = (void **)((char *)*head + next_off);
		while (*current_next != NULL)
			current_next = (void **)((char *)(*current_next) + next_off);
		*current_next = node;
		new_node_prev = (void **)((char *)node + prev_off);
		*new_node_prev = (void *)((char *)current_next - next_off);
		new_node_next = (void **)((char *)node + next_off);
		*new_node_next = NULL;
	}
}

void	pexe_malloc(t_msh *msh, t_parse *prs)
{
	msh->pexe = malloc(sizeof(t_pexe));
	if (msh->pexe == NULL)
		exit_cleanup("Malloc Failed", msh, errno);
	clean_init_pexe_node(msh->pexe);
}

t_token	*token_malloc(t_msh *msh, t_parse *prs)
{
	t_token	*tkn;

	tkn = malloc(sizeof(t_token));
	if (tkn == NULL)
		exit_cleanup("Malloc Failed", msh, errno);
	clean_init_token_node(tkn);
}

void	parse_malloc(t_msh *msh, t_parse *prs)
{
	prs = malloc(sizeof(t_parse));
	if (prs == NULL)
		exit_cleanup("Malloc Failed", msh, errno);
	clean_init_parse(prs);
	msh->parse = prs;
}
