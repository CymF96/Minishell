/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coline <coline@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:00:34 by cofische          #+#    #+#             */
/*   Updated: 2024/11/07 15:52:48 by coline           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	chd1_fork(t_msh *msh, int nb_chds)
{
	msh->chds[0]->pid = fork();
	if (msh->chds[0]->pid == 0)
	{
		close(msh->chds[0]->fd[0]);
		dup2(msh->chds[0]->fd[1], STDOUT_FILENO);
		close(msh->chds[0]->fd[1]);
		close_fds(msh, nb_chds, 0);
		check_type(msh);
	}
}

void	mdlchd_fork(t_msh *msh, int i, int nb_chds)
{
	msh->chds[i]->pid = fork();
	if (msh->chds[i]->pid == 0)
	{
		dup2(msh->chds[i - 1]->fd[0], STDIN_FILENO);
		close(msh->chds[i - 1]->fd[0]);
		close(msh->chds[i]->fd[0]);
		dup2(msh->chds[i]->fd[1], STDOUT_FILENO);
		close(msh->chds[i]->fd[1]);
		close_fds(msh, nb_chds, i);
		check_type(msh);
	}
}

void	last_fork(t_msh *msh, int i, int nb_chds)
{
	msh->chds[i]->pid = fork();
	if (msh->chds[i]->pid == 0)
	{
		dup2(msh->chds[i - 1]->fd[0], STDIN_FILENO);
		close(msh->chds[i - 1]->fd[0]);
		close_fds(msh, nb_chds, -1);
		check_type(msh);
	}
}

int	kill_children(t_msh *msh, int status, int i)
{
	int	j;

	if (WIFSIGNALED(status))
	{
		j = 0;
		while (j != i && msh->chds[j] != NULL)
		{
			kill(msh->chds[j]->pid, SIGTERM);
			j++;
		}
		return (1);
	}
	return (0);
}

void	closing(t_msh *msh, int nb_chds)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	close_fds(msh, nb_chds, -1);
	dup2(msh->fd[0], STDIN_FILENO);
	close(msh->fd[0]);
	dup2(msh->fd[1], STDOUT_FILENO);
	close(msh->fd[1]);
	while (msh->chds && msh->chds[i] != NULL)
	{
		waitpid(msh->chds[i]->pid, &status, 0);
		if (kill_children(msh, status, i) == 1)
			break ;
		i++;
	}
	if (msh->chds != NULL)
	{
		free_pipex(msh);
		msh->chds = NULL;
	}
	exit_cleanup(NULL, msh, WIFEXITED(status), 0);
}
