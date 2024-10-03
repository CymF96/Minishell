/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_structures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:53:54 by mcoskune          #+#    #+#             */
/*   Updated: 2024/10/03 11:55:39 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_pipex(t_pipex **children)
{
	int	i;

	i = 0;
	while (children[i] != NULL)
	{
		free(children[i]);
		children[i] = NULL;
		i++;
	}
}

void	free_pexe(t_msh *msh)
{
	t_pexe	*current;
	t_pexe	*next;

	current = head(msh->pexe);
	while (current != NULL)
	{
		next = current->next;
		if (current->option != NULL)
			free_mallocs(NULL, (void **)current->option);
		current->prev = NULL;
		if (current->temp != NULL)
			free(current->temp);
		free(current);
		current = NULL;
		current = next;
	}
	msh->pexe = NULL;
}

void	free_parse(t_msh *msh)
{
	t_token	*temp;

	if (msh->parse != NULL)
	{
		free_mallocs ((void *)msh->parse->modified, (void **)msh->parse->poi);
		while (msh->parse->head != NULL)
		{
			if (msh->parse->head != NULL)
			{
				temp = msh->parse->head->next;
				free (msh->parse->head->token);
				msh->parse->head->token = NULL;
				free (msh->parse->head);
				msh->parse->head = temp;
			}
		}
		free(msh->parse);
		msh->parse = NULL;
	}
}
