#include "../minishell.h"

void	double_red_right(t_msh *msh)
{
	int		save_sdtout;
	int		g;
	
	save_sdtout = dup(STDOUT_FILENO);
	g = msh->pexe->group_id;
	msh->fd[1] = open(msh->pexe->cmd, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (msh->fd[1] == -1)
	{
		exit_cleanup(NULL, msh, error erno, 0);
		return ;
	}
	if (dup2(msh->fd[1], STDOUT_FILENO) < 0)
		{
			perror("dup2\n");
			close(msh->fd[1]);
		}
	close(msh->fd[1]);
	if (msh->pexe->next != NULL && msh->pexe->next->group_id == g)
		msh->pexe = msh->pexe->next;
	check_type(msh);
	msh->fd[1] = save_sdtout;
	dup2(msh->fd[1], STDOUT_FILENO);
}

void	red_left(t_msh *msh)
{
	int	g;
	int	save_stdin;
	
	g = msh->pexe->group_id;
	save_stdin = dup(STDIN_FILENO);
	msh->fd[0] = open(msh->pexe->cmd, O_RDONLY, 0664);
	if (msh->fd[0] == -1)
	{
		exit_cleanup(NULL, msh, errno, 0);
		return ;
	}
	if (dup2(msh->fd[0], STDIN_FILENO) < 0)
		{
			perror("dup2\n");
			close(msh->fd[0]);
		}
	close(msh->fd[0]);
	if (msh->pexe->next != NULL && msh->pexe->next->group_id == g)
		msh->pexe = msh->pexe->next;
	check_type(msh);
	msh->fd[0] = save_stdin;
	dup2(msh->fd[0], STDIN_FILENO);
}

void	red_right(t_msh *msh)
{
	int	g;
	int	save_sdtout;
	
	g = msh->pexe->group_id;
	save_sdtout = dup(STDOUT_FILENO);
	msh->fd[1] = open(msh->pexe->cmd, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (msh->fd[1] == -1)
	{
		exit_cleanup(NULL, msh, errno, 0);
		return ;
	}
	if (dup2(msh->fd[1], STDOUT_FILENO) < 0)
	{
		perror("dup2\n");
		close(msh->fd[1]);
	}
	close(msh->fd[1]);
	if (msh->pexe->next)
		msh->pexe = msh->pexe->next;
	check_type(msh);
	msh->fd[1] = save_sdtout;
	dup2(msh->fd[1], STDOUT_FILENO);
}
