#include "../minishell.h"

void	double_red_right(t_msh *msh)
{
	int		save_sdtout;

	save_sdtout = dup(STDOUT_FILENO);
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
	{
		check_type(msh);
		msh->fd[1] = save_sdtout;
		dup2(msh->fd[1], STDOUT_FILENO);
		if (!msh->child)
			close(msh->fd[1]);
	}
}

void	red_left(t_msh *msh)
{
	int	save_stdin;

	save_stdin = dup(STDIN_FILENO);
	msh->fd[0] = open(msh->pexe->cmd, O_RDONLY, 0664);
	if (msh->fd[0] == -1)
		exit_cleanup(NULL, msh, errno, 0);
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
	}
}

void	red_right(t_msh *msh)
{
	int	save_sdtout;

	save_sdtout = dup(STDOUT_FILENO);
	msh->fd[1] = open(msh->pexe->cmd, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (msh->fd[1] == -1)
		exit_cleanup(NULL, msh, errno, 2);
	if (dup2(msh->fd[1], STDOUT_FILENO) < 0)
	{
		close(msh->fd[1]);
		exit_cleanup(NULL, msh, errno, 0);
	}
	if (move_node(msh))
	{
		check_type(msh);
		close(msh->fd[1]);
		msh->fd[1] = save_sdtout;
		dup2(msh->fd[1], STDOUT_FILENO);
	}
}
