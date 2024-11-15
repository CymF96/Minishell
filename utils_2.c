/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofische <cofische@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:32:51 by mcoskune          #+#    #+#             */
/*   Updated: 2024/11/14 08:28:53 by cofische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_pexe	*set_last_nodes(t_pexe *head, int group_id)
{
	t_pexe	*last;

	last = head;
	while (head && head->group_id == group_id)
	{
		if (head->type == INFILE || head->type == HEREDOC)
			last = head;
		if ((head->type != INFILE && head->type != HEREDOC) && !head->next)
			return (last);
		else
			head = head->next;
	}
	return (last);
}

void	remove_node(t_pexe *node)
{
	if (node)
	{
		if (node->prev)
			node->prev->next = node->next;
		if (node->next)
			node->next->prev = node->prev;
		if (node->type == HEREDOC)
			unlink(node->cmd);
		if (node->cmd)
		{
			free(node->cmd);
			node->cmd = NULL;
		}
		free(node);
		node = NULL;
	}
}

t_pexe	*clean_group_nodes(t_pexe *current, int g, t_pexe *last_node)
{
	t_pexe	*next;

	while (current && current->group_id == g)
	{
		next = current->next;
		if (last_node != current && (current->type == INFILE \
			|| current->type == HEREDOC))
			remove_node(current);
		if (!next)
			return (current);
		current = next;
	}
	return (current);
}

int	pexe_length(t_msh *msh)
{
	t_pexe	*current;
	int		g;
	int		nb_g;

	current = msh->pexe;
	g = current->group_id;
	nb_g = 0;
	while (current)
	{
		while (current && current->group_id == g)
			current = current->next;
		nb_g++;
		g++;
	}
	return (nb_g);
}

void	clean_groups(t_msh *msh, int g)
{
	t_pexe	*current;
	t_pexe	*last_node;
	int		nb_group;

	nb_group = pexe_length(msh);
	current = msh->pexe;
	while (current && nb_group != 0)
	{
		g = current->group_id;
		while (current && (current->type != HEREDOC && current->type != INFILE))
			current = current->next;
		if (current)
		{
			last_node = set_last_nodes(current, g);
			current = clean_group_nodes(current, g, last_node);
			msh->pexe = current;
		}
		if (current && current->next)
			current = current->next;
		nb_group--;
	}
	while (msh->pexe->prev != NULL)
		msh->pexe = msh->pexe->prev;
}
