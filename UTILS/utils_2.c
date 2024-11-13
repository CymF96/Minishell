/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coline <coline@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:32:51 by mcoskune          #+#    #+#             */
/*   Updated: 2024/11/13 12:23:16 by coline           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_pexe	*set_last_nodes(t_pexe *head, int group_id)
{
	t_pexe	*last;

	last = head;
	while (head && head->group_id == group_id)
	{
		last = head;
		head = head->next;
	}
	return (last);
}

void	remove_node(t_pexe *node)
{
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	if (node->type == HEREDOC)
		unlink(node->cmd);
	free(node->cmd);
	free(node);
}

void	clean_group_nodes(t_pexe *current, int g, t_pexe *last_node)
{
	t_pexe	*next;

	while (current && current->group_id == g)
	{
		next = current->next;
		if (strncmp(current->cmd, last_node->cmd, ft_strlen(last_node->cmd)))
			remove_node(current);
		current = next;
	}
}

int	pexe_length(t_msh *msh)
{
	t_pexe	*current;
	int g;
	int nb_g;

	current = msh->pexe;
	g = current->group_id;
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
	t_pexe	*head;
	t_pexe	*last_node;
	int		nb_group;

	head = msh->pexe;
	nb_group = pexe_length(msh);
	current = msh->pexe;
	while (nb_group)
	{
		g = current->group_id;
		while (current && (current->type != HEREDOC && current->type != INFILE))
			current = current->next;
		if (current)
		{
			last_node = set_last_nodes(current, g);
			clean_group_nodes(current, g, last_node);
		}
		if (current->next)
			current = current->next;
		nb_group--;
	}
	msh->pexe = head;
}
