/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mallocs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:24:52 by mcoskune          #+#    #+#             */
/*   Updated: 2024/08/28 12:36:50 by mcoskune         ###   ########.fr       */
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

t_pexe	*pexe_malloc(t_msh *msh)//t_parse *prs parameter
{
	t_pexe	*temp;
	int		i;

	i = 0;
	temp = malloc(sizeof(t_pexe));
	if (temp == NULL)
		exit_cleanup("Malloc Failed", msh, errno, 2);//verifiy the correct exit check
	clean_init_pexe_node(temp);
	temp->option = malloc(sizeof(char *) * 4);
	if (temp->option == NULL)
		exit_cleanup("Malloc failed", msh, errno, 2);//verifiy the correct exit check
	while (i < 4)
		temp->option[i++] = NULL;
	return (temp);
}

t_token	*token_malloc(t_msh *msh) //t_parse *prs parameter
{
	t_token	*tkn;

	tkn = malloc(sizeof(t_token));
	if (tkn == NULL)
		exit_cleanup("Malloc Failed", msh, errno, 2);//verifiy the correct exit check
	clean_init_token_node(tkn);
	return (tkn);
}

void	parse_malloc(t_msh *msh)
{
	t_parse	*prs;
	int	i;

	i = 0;
	prs = malloc(sizeof(t_parse));
	if (prs == NULL)
		exit_cleanup("Malloc Failed", msh, errno, 2); //verifiy the correct exit check
	clean_init_parse(prs);
	msh->parse = prs;
	prs->modified = malloc(sizeof(char) * 2000);
	if (prs->modified == NULL)
		exit_cleanup("Malloc failed", msh, errno, 2);//verifiy the correct exit check
	prs->size_modified = 1000;
	prs->poi = malloc(sizeof(int *) * 100);
	if (prs->poi == NULL)
		exit_cleanup("Malloc failed", msh, errno, 2);//verifiy the correct exit check
	while (i < 100)
		prs->poi[i++] = NULL;
}
