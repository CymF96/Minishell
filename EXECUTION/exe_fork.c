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

void	mdlchd_fork(t_msh *msh, t_pipex **chds)
{
	if ((chds[1]->pid = fork()) == 0)
	{
		close(chds[0]->fd[1]);
		dup2(chds[0]->fd[0], STDIN_FILENO);
		close(chds[0]->fd[0]);
		close(chds[1]->fd[0]);
		dup2(chds[1]->fd[1], STDOUT_FILENO);
		close(chds[1]->fd[1]);
		check_type(msh);// problem here for exit the process as the parent is waiting for it finish
	}
}

void	lstchd_fork(t_msh *msh, t_pipex **chds)
{
	if ((chds[2]->pid = fork()) == 0)
	{
		close(chds[0]->fd[0]);
		close(chds[0]->fd[1]);
		close(chds[1]->fd[1]);
		dup2(chds[1]->fd[0], STDIN_FILENO);
		close(chds[1]->fd[0]);
		check_type(msh);
	}
}

void	kill_children(t_pipex **chds) //t_msh *msh
{
	int	i;

	i = 0;
	while (chds[i] != NULL)
	{
		if (chds[i] != NULL && waitpid(chds[i]->pid, NULL, WNOHANG) == 0)
			kill(chds[i]->pid, SIGTERM);
		i++;
	}
	i = 0;
	while (chds[i] != NULL)
	{
		if (chds[i] != NULL)
		{
			if (waitpid(chds[i]->pid, NULL, 0) == -1)
				perror("Error");
        	i++;
		}
	}
}


void	closing(t_msh *msh, t_pipex **chds)
{
	int	i;
	int	flag;
	int status;

	i = 0;
	flag = 1;
	while (chds[i+1] != NULL)
	{
		close(chds[i]->fd[0]);
		close(chds[i]->fd[1]);
		i++;
	}
	i = 0;
	while (chds[i] != NULL)
	{
		waitpid(chds[i]->pid, &status, 0);
		if ((WIFSIGNALED(status)))
			flag = 1;
		i++;
	}
	if (!flag)
		kill_children(chds);
	free_pipex(chds);
	if (chds != NULL)
		free(chds);
	chds = NULL;
	exit_cleanup(NULL, msh, errno, 0);
}
