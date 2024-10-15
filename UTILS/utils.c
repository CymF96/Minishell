/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:45:44 by mcoskune          #+#    #+#             */
/*   Updated: 2024/10/15 10:16:36 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	node_strlen(t_pexe *node)
{
	int	len;
	int	g;

	g = node->group_id;
	len = 0;
	while (node != NULL && node->group_id == g)
	{
		len++;
		node = node->next;
	}
	return (len);
}

int	move_node(t_msh *msh)
{
	int	g;

	g = msh->pexe->group_id;
	if (msh->pexe->next != NULL \
			&& msh->pexe->next->group_id == g \
			&& msh->pexe->next->cmd != NULL)
	{
		msh->pexe = msh->pexe->next;
		return (1);
	}
	return (0);
}

void	move_group(t_msh *msh)
{
	int	g;

	g = msh->pexe->group_id;
	while (msh->pexe != NULL \
			&& msh->pexe->group_id == g \
			&& msh->pexe->cmd != NULL)
		msh->pexe = msh->pexe->next;
}

void	swap(t_pexe *node_a, t_pexe *node_b)
{
	t_pexe	temp;

	temp.cmd = node_a->cmd;
	temp.group_id = node_a->group_id;
	temp.p_index = node_a->p_index;
	temp.option = node_a->option;
	temp.type = node_a->type;
	node_a->cmd = node_b->cmd;
	node_a->group_id = node_b->group_id;
	node_a->p_index = node_b->p_index;
	node_a->option = node_b->option;
	node_a->type = node_b->type;
	node_b->cmd = temp.cmd;
	node_b->group_id = temp.group_id;
	node_b->p_index = temp.p_index;
	node_b->option = temp.option;
	node_b->type = temp.type;
}
