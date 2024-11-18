/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofische <cofische@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:00:46 by cofische          #+#    #+#             */
/*   Updated: 2024/11/18 13:34:36 by cofische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_fds(t_msh *msh, int nb_chds, int current)
{
	int	i;

	i = 0;
	while (i < nb_chds - 1)
	{
		if (i != current)
		{
			close(msh->chds[i]->fd[0]);
			close(msh->chds[i]->fd[1]);
		}
		i++;
	}
	if (msh->fd[0] != -1)
	{
		close(msh->fd[0]);
		msh->fd[0] = -1;
	}
	if (msh->fd[1] != -1)
	{
		close(msh->fd[1]);
		msh->fd[1] = -1;
	}
}

int	create_children(t_msh *msh)
{
	int	nb_chds;
	int	i;

	nb_chds = msh->pipe_nb + 1;
	i = 0;
	msh->chds = malloc(sizeof(t_pipex *) * (msh->pipe_nb + 2));
	if (msh->chds == NULL)
		exit_cleanup(NULL, msh, errno, 2);
	while (msh->pipe_nb >= 0)
	{
		msh->chds[i] = (t_pipex *)malloc(sizeof(t_pipex));
		if (msh->chds[i] == NULL)
		{
			free_pipex(msh);
			exit_cleanup("Error handling pipe\n", msh, 1, 0);
			return (0);
		}
		clean_init_chds(msh->chds[i]);
		msh->pipe_nb--;
		i++;
	}
	msh->chds[i] = NULL;
	return (nb_chds);
}

void	create_pipes(t_msh *msh)
{
	int	i;

	i = 0;
	while (msh->chds[i + 1] != NULL)
	{
		if (pipe(msh->chds[i]->fd) == -1)
		{
			free_pipex(msh);
			exit_cleanup(NULL, msh, errno, 0);
		}
		i++;
	}
}

void	ft_pipex(t_msh *msh)
{
	int	i;
	int	nb_chds;

	i = 0;
	msh->fd[0] = dup(STDIN_FILENO);
	msh->fd[1] = dup(STDOUT_FILENO);
	nb_chds = create_children(msh);
	create_pipes(msh);
	chd1_fork(msh, nb_chds);
	i = 1;
	while (msh->chds[i + 1] != NULL)
	{
		move_group(msh);
		mdlchd_fork(msh, i, nb_chds);
		i++;
	}
	move_group(msh);
	last_fork(msh, i, nb_chds);
	closing(msh, nb_chds);
}
