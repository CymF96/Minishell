/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofische <cofische@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:00:13 by mcoskune          #+#    #+#             */
/*   Updated: 2025/05/28 19:31:52 by cofische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

void	free_envp(t_msh *msh)
{
	int	i;

	i = 0;
	if (msh->envp != NULL)
	{
		while (msh->envp[i] != NULL)
			free(msh->envp[i++]);
		free(msh->envp);
	}
}

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

void	handle_message(int check, char *msg)
{
	if (check == 1 || check == 2)
	{
		rl_clear_history();
		if (check == 2)
		{
			perror("Error - ");
			if (msg != NULL)
				printf("Reason - %s\n", msg);
		}
	}
}

void	exit_cleanup(char *msg, t_msh *msh, int flag, int check)
{
	if (msg != NULL)
	{
		ft_putstr_fd(msg, STDERR_FILENO);
		write(STDERR_FILENO, "\n", 1);
	}
	if (check == 1 || check == 2)
	{
		clear_msh(msh, check, msg);
		free_envp(msh);
		if (check == 1)
			exit(msh->exit_error);
		exit(msh->exit_error);
	}
	clear_msh(msh, check, NULL);
	if (flag != 0)
		msh->exit_error = flag;
}
