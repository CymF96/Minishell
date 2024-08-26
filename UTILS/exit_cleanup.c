/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:00:13 by mcoskune          #+#    #+#             */
/*   Updated: 2024/08/26 14:02:02 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_mallocs(void *s_ptr, void **d_ptr)
{
	int	i;

	if (s_ptr != NULL)
	{
		free(s_ptr);
		s_ptr = NULL;
	}
	if (d_ptr != NULL)
	{
		i = 0;
		while (d_ptr[i] != NULL)
		{
			free(d_ptr);
			i++;
		}
		d_ptr = NULL;
	}
}

void	free_pexe(t_msh *msh)
{
	t_pexe	*temp;

	while (msh->pexe != NULL)
	{
		temp = msh->pexe->next;
		free_mallocs(msh->pexe->cmd, msh->pexe->option);
		free(msh->pexe);
		msh->pexe = temp;
	}
	msh->pexe = NULL;
}

void	free_parse(t_msh *msh)
{
	t_token	*temp;

	if (msh->parse != NULL)
	{
		while (msh->parse->head != NULL)
		{
			if (temp->token != NULL)
				free (temp->token);
			temp = msh->parse->head->next;
			free (msh->parse->head);
			msh->parse->head = temp;
		}
		free(msh->parse);
		msh->parse = NULL;
	}
}

void	exit_cleanup(char *msg, t_msh *msh, int flag, int check)
{
	if (msg != NULL)
		printf("Program Termination Reason - %s\n", msg);
	if (msh->input != NULL)
		free(msh->input);
	free_parse(msh);
	free_pexe(msh);
	//rl_clear_history();
	if (check == -1)
		exit(flag);
}
