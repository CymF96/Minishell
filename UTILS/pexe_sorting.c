/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pexe_sorting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 20:45:51 by mcoskune          #+#    #+#             */
/*   Updated: 2024/10/14 22:54:46 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_remove_heredoc(t_msh *msh, int heredoc, int infile, int g)
{
	t_pexe	*delme;
	t_pexe	*current;

	current = msh->pexe;
	while (current != NULL)
	{
		if (current->type == HEREDOC && heredoc && infile \
				&& current->group_id == g)
		{
			delme = current;
			current = current->next;
			current->prev = delme->prev;
			if (delme->prev != NULL)
				delme->prev->next = current;
			else
				msh->pexe = current;
			unlink(delme->cmd);
			free(delme->cmd);
			delme->cmd = NULL;
			free(delme);
			delme = NULL;
		}
		current = current->next;
	}
}

void	check_heredoc_infile(t_msh *msh)
{
	int		heredoc;
	int		infile;
	int		g_infile;
	t_pexe	*head;

	head = msh->pexe;
	heredoc = 0;
	infile = 0;
	while (msh->pexe != NULL)
	{
		if (msh->pexe->type == HEREDOC)
			heredoc = 1;
		if (msh->pexe->type == INFILE)
		{
			infile = 1;
			g_infile = msh->pexe->group_id;
		}
		msh->pexe = msh->pexe->next;
	}
	msh->pexe = head;
	check_remove_heredoc(msh, heredoc, infile, g_infile);
}

void	check_double_heredoc(t_msh *msh)
{
	t_pexe	*head;
	int		heredoc;
	int		g;

	heredoc = 0;
	head = msh->pexe;
	while (msh->pexe != NULL)
	{
		if (msh->pexe->type == HEREDOC)
		{
			g = msh->pexe->group_id;
			heredoc++;
		}
		msh->pexe = msh->pexe->next;
	}
	msh->pexe = head;
	remove_node(msh, heredoc, g);
	if (head)
		msh->pexe = head;
}

int	check_swapping(t_pexe *current, t_pexe *next)
{
	if (current->group_id > next->group_id || \
			(current->group_id == next->group_id \
			&& current->p_index > next->p_index))
	{
		swap(current, next);
		if (current->type == HEREDOC && next->type == STRING \
				&& current->group_id == next->group_id)
			next->p_index = current->p_index + 1;
		return (1);
	}
	return (0);
}

void	sort_pexe(t_msh *msh)
{
	t_pexe	*current;
	t_pexe	*next;
	int		loop;

	loop = 1;
	while (loop)
	{
		loop = 0;
		current = msh->pexe;
		while (current != NULL && current->next != NULL)
		{
			next = current->next;
			if (check_swapping(current, next))
				loop = 1;
			current = current->next;
		}
	}
	check_heredoc_infile(msh);
	check_double_heredoc(msh);
}
