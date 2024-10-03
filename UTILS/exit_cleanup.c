/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:00:13 by mcoskune          #+#    #+#             */
/*   Updated: 2024/10/03 13:21:19 by mcoskune         ###   ########.fr       */
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
			free(d_ptr[i]);
			d_ptr[i] = NULL;
			i++;
		}
		free(d_ptr);
		d_ptr = NULL;
	}
}

t_pexe	*head(t_pexe *current)
{
	while (current->prev != NULL)
		current = current->prev;
	return (current);
}

static void	handle_message(int check, char *msg)
{
	if (check == 1 || check == 2)
	{
		rl_clear_history();
		if (msg != NULL && check == 1)
			printf("Exit Success - %s\n", msg);
		else if (check == 2)
		{
			perror("Error - ");
			if (msg != NULL)
				printf("Reason - %s\n", msg);
		}
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
	if (msh->parse != NULL)
		free_parse(msh);
	if (msh->pexe != NULL)
		free_pexe(msh);
	if (msh->input != NULL)
	{
		free(msh->input);
		msh->input = NULL;
	}
	if (msh->fd[0] != -1)
		close(msh->fd[0]);
	if (msh->fd[1] != -1)
		close(msh->fd[1]);
	handle_message(check, msg);
}

// Main cleanup function. Takes optional message to output, main data struct,
// errno for flag, and check is for programmers. 1 is for exit success, 2 for
// exit due to failure, 3 for cleaning up the mallocs for next input
void	exit_cleanup(char *msg, t_msh *msh, int flag, int check)
{
	int	i;

	if (msg)
		ft_printf("%s\n", msg);
	if (check == 1 || check == 2)
	{
		clear_msh(msh, check, msg);
		if (msh != NULL)
		{
			i = 0;
			if (msh->envp != NULL)
			{
				while (msh->envp[i] != NULL)
					free(msh->envp[i++]);
				free(msh->envp);
			}
			free(msh);
		}
		if (check == 1)
			exit(EXIT_SUCCESS);
		exit(EXIT_FAILURE);
	}
	clear_msh(msh, check, NULL);
	if (flag != 0)
		msh->exit_error = flag;
}
