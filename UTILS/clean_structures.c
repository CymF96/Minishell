/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_structures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:53:54 by mcoskune          #+#    #+#             */
/*   Updated: 2024/10/03 14:34:40 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_pipex(t_msh *msh)
{
	int	i;

	i = 0;
	if (!msh->child)
		free(msh->chds[0]);
	else
	{
		while (msh->chds[i] != NULL)
		{
			free(msh->chds[i]);
			msh->chds[i] = NULL;
			i++;
		}
	}
	free(msh->chds);
}

void	free_pexe(t_msh *msh)
{
	t_pexe	*next;

	msh->pexe = head(msh->pexe);
	while (msh->pexe != NULL)
	{
		next = msh->pexe->next;
		if (msh->pexe->type == HEREDOC)
			unlink(msh->pexe->cmd);
		if (msh->pexe->option != NULL)
			free_mallocs(NULL, (void **)msh->pexe->option);
		if (msh->pexe->cmd != NULL)
			free(msh->pexe->cmd);
		free(msh->pexe);
		msh->pexe = NULL;
		msh->pexe = next;
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

void	clear_msh2(t_msh *msh)
{
	if (msh->parse != NULL)
		free_parse(msh);
	if (msh->pexe != NULL)
		free_pexe(msh);
	if (msh->input != NULL)
	{
		free(msh->input);
		msh->input = NULL;
	}
	if (msh->child)
	{
		if (msh->fd[0] != -1)
		close(msh->fd[0]);
		if (msh->fd[1] != -1)
		close(msh->fd[1]);
	}
}

void	clear_msh(t_msh *msh, int check, char *msg)
{
	if (msh == NULL)
		return ;
	if (msh->heredoc != NULL)
	{
		unlink(msh->heredoc);
		free(msh->heredoc);
		msh->heredoc = NULL;
	}
	if (msh->path != NULL)
	{
		free(msh->path);
		msh->path = NULL;
	}
	if (msh->chds != NULL)
	{
		free_pipex(msh);
		msh->chds = NULL;
	}
	clear_msh2(msh);
	handle_message(check, msg);
}

t_pexe	*head(t_pexe *current)
{
	while (current->prev != NULL)
		current = current->prev;
	return (current);
}