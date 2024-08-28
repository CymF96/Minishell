#include "../minishell.h"

void	chd1_fork(t_msh *msh, t_pipex *chds)
{
	if ((chds->pid = fork()) == 0)
	{
		close(chds->fd[0]);
		dup2(chds->fd[1], STDOUT_FILENO);
		close(chds->fd[1]);
		check_type(msh);
	}
}

void	mdlchd_fork(t_msh *msh, t_pipex *prev_chds, t_pipex *chds)
{
	if ((chds->pid = fork()) == 0)
	{
		close(prev_chds->fd[1]);
		dup2(prev_chds->fd[0], STDIN_FILENO);
		close(prev_chds->fd[0]);
		close(chds->fd[0]);
		dup2(chds->fd[1], STDOUT_FILENO);
		close(chds->fd[1]);
		check_type(msh);
	}
}

void	lstchd_fork(t_msh *msh, t_pipex *prev_chds, t_pipex *chds)
{
	if ((chds->pid = fork()) == 0)
	{
		close(prev_chds->fd[1]);
		dup2(prev_chds->fd[0], STDIN_FILENO);
		close(prev_chds->fd[0]);
		check_type(msh);
	}
}

void	kill_children(t_msh *msh, t_pipex **chds, int chd_index)
{
	int	i;

	i = 0;
	while (i < chd_index - 1)
	{
		if (chds[i] != NULL && waitpid(chds[i]->pid, NULL, WNOHANG) == 0)
			kill(chds[i]->pid, SIGTERM);
		i++;
	}
	i = 0;
	while (i < chd_index - 1)
	{
		if (chds[i] != NULL)
		{
			if (waitpid(chds[i]->pid, NULL, 0) == -1)
				perror("Error");
        	i++;
		}
	}
}


void	closing(t_msh *msh, t_pipex **chds, int chd_index)
{
	int	i;
	int	flag;
	int status;

	i = 0;
	flag = 1;
	while (i < (chd_index - 1))
	{
		close(chds[i]->fd[0]);
		close(chds[i++]->fd[1]);
	}
	i = 0;
	while (i < chd_index)
	{
		waitpid(chds[i]->pid, &status, 0);
		if ((WIFSIGNALED(status)))
			flag = 0;
	}
	if (!flag)
		kill_children(msh, chds, chd_index);
	free_pipex(chds);
}
