#include "../minishell.h"

void	open_append_output(t_msh *msh)
{
	if (msh->pexe->next != NULL\
		&& msh->pexe->next->group_id == msh->pexe->group_id)
	{
		if (msh->pexe->next->type == 7 && msh->pexe->next->cmd != NULL)
		{
			msh->pexe = msh->pexe->next;
			msh->fd[1] = open(msh->pexe->cmd, O_RDONLY, O_APPEND, 664);
		}
		if (dup2(msh->fd[1], STDOUT_FILENO) < 0)
		{
			perror("dup2\n");
			close(msh->fd[1]);
		}
		close(msh->fd[1]);
	}
}

void	double_red_right(t_msh *msh)
{
	pid_t	pids;
	int		save_sdtout;
	
	save_sdtout = dup(STDOUT_FILENO);
	open_append_output(msh);
	if (msh->pexe->next)
		msh->pexe = msh->pexe->next;
	pids = fork();
	if (pids == 0)
		check_type(msh);
	else
	{
		wait(NULL);
		msh->fd[0] = 0;
		msh->fd[1] = 1;
		dup2(save_sdtout, STDOUT_FILENO);
	}
}

void	open_file_input(t_msh *msh)
{
	if (msh->pexe->next != NULL\
		&& msh->pexe->next->group_id == msh->pexe->group_id)
	{
		if (msh->pexe->next->type == 7 && msh->pexe->next->cmd != NULL)
		{
			msh->pexe = msh->pexe->next;
			msh->fd[0] = open(msh->pexe->cmd, O_RDONLY, 664);
		}
		if (dup2(msh->fd[0], STDIN_FILENO) < 0)
		{
			perror("dup2\n");
			close(msh->fd[0]);
		}
		close(msh->fd[0]);
	}
}
