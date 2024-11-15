/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:00:52 by cofische          #+#    #+#             */
/*   Updated: 2024/11/15 10:53:38 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_redirection(t_msh *msh, int save_sdtout)
{
	check_type(msh);
	if (msh->hr_flag && !msh->child)
		dup2(0, STDOUT_FILENO);
	else if (!msh->child)
	{
		msh->fd[1] = save_sdtout;
		dup2(msh->fd[1], STDOUT_FILENO);
		close(msh->fd[1]);
		msh->fd[1] = -1;
	}
	else
		exit_cleanup(NULL, msh, 0, 1);
	dup2(0, STDOUT_FILENO);
}

int	open_heredoc(t_msh *msh)
{
	if (msh->pexe->type == HEREDOC)
		msh->heredoc = ft_strdup(msh->pexe->cmd);
	msh->fd[0] = open(msh->pexe->cmd, O_RDONLY, 0664);
	if (msh->fd[0] == -1)
	{
		exit_cleanup(NULL, msh, errno, 0);
		return (1);
	}
	return (0);
}

void	double_red_right(t_msh *msh)
{
	int		save_sdtout;

	save_sdtout = dup(STDOUT_FILENO);
	if (msh->fd[1] != -1)
		close(msh->fd[1]);
	msh->fd[1] = open(msh->pexe->cmd, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (msh->fd[1] == -1)
		exit_cleanup(NULL, msh, errno, 0);
	if (dup2(msh->fd[1], STDOUT_FILENO) < 0)
	{
		close(msh->fd[1]);
		exit_cleanup(NULL, msh, errno, 0);
	}
	close(msh->fd[1]);
	if (move_node(msh))
		close_redirection(msh, save_sdtout);
}

void	red_left(t_msh *msh)
{
	int		save_stdin;

	save_stdin = dup(STDIN_FILENO);
	if (msh->fd[0] != -1)
		close(msh->fd[0]);
	if (open_heredoc(msh) == 1)
		return ;
	if (dup2(msh->fd[0], STDIN_FILENO) < 0)
	{
		close(msh->fd[1]);
		exit_cleanup(NULL, msh, errno, 0);
	}
	close(msh->fd[0]);
	if (move_node(msh))
	{
		check_type(msh);
		msh->fd[0] = save_stdin;
		dup2(msh->fd[0], STDIN_FILENO);
		close(msh->fd[0]);
		msh->fd[0] = -1;
	}
}

void	red_right(t_msh *msh)
{
	int	save_sdtout;

	save_sdtout = dup(STDOUT_FILENO);
	if (msh->fd[1] != -1)
		close(msh->fd[1]);
	msh->fd[1] = open(msh->pexe->cmd, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (msh->fd[1] == -1)
		exit_cleanup(NULL, msh, errno, 2);
	if (dup2(msh->fd[1], STDOUT_FILENO) < 0)
	{
		close(msh->fd[1]);
		exit_cleanup(NULL, msh, errno, 0);
	}
	close(msh->fd[1]);
	if (move_node(msh))
		close_redirection(msh, save_sdtout);
}
