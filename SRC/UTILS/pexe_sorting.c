/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pexe_sorting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofische <cofische@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 20:45:51 by mcoskune          #+#    #+#             */
/*   Updated: 2025/05/28 18:00:30 by cofische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

int	check_access(t_msh *msh, t_pexe *pexe, int *heredoc, int *infile)
{
	int	temp_fd;

	if (pexe->type == INFILE || pexe->type == HEREDOC)
	{
		temp_fd = open(msh->pexe->cmd, O_RDONLY, 0664);
		if (temp_fd < 0)
		{
			printf("%s: No such file or directory\n", pexe->cmd);
			msh->exit_error = 2;
			return (1);
		}
		close(temp_fd);
	}
	if (pexe->type == HEREDOC)
		(*heredoc)++;
	if (pexe->type == INFILE)
		(*infile)++;
	return (0);
}

int	check_heredoc_infile(t_msh *msh)
{
	int		g;
	t_pexe	*head;
	int		heredoc;
	int		infile;

	heredoc = 0;
	infile = 0;
	head = msh->pexe;
	while (msh->pexe != NULL)
	{
		if (check_access(msh, msh->pexe, &heredoc, &infile))
			return (1);
		msh->pexe = msh->pexe->next;
	}
	msh->pexe = head;
	g = head->group_id;
	if ((heredoc && infile) || (heredoc > 1 && infile == 0) \
		|| (heredoc == 0 && infile > 1))
		clean_groups(msh, g);
	return (0);
}

int	check_swapping(t_pexe *current, t_pexe *next)
{
	if (current->type == EXE && next->type == INFILE)
	{
		swap(current, next);
		current->p_index = next->p_index;
		next->p_index = current->p_index + 1;
	}
	else if (current->group_id > next->group_id || \
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

int	sort_pexe(t_msh *msh)
{
	t_pexe	*current;
	t_pexe	*next;
	int		loop;

	if (check_heredoc_infile(msh))
		return (1);
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
	return (0);
}
