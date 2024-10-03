#include "../minishell.h"

void	chd1_fork(t_msh *msh, int nb_chds)
{
	msh->chds[0]->pid = fork();
	if (msh->chds[0]->pid == 0)
	{
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
		close_fds(msh, nb_chds, i);
		check_type(msh);
	}
}

void	kill_children(t_msh *msh)
{
	int	i;
	int	status;

	i = 0;
	while (msh->chds[i] != NULL)
	{
		if (waitpid(msh->chds[i]->pid, &status, WNOHANG) == 0)
			kill(msh->chds[i]->pid, SIGTERM);
		i++;
	}
	i = 0;
	while (msh->chds[i] != NULL)
	{
		if (waitpid(msh->chds[i]->pid, &status, 0) == -1)
			perror("Error");
		i++;
	}
}

void	closing(t_msh *msh, int nb_chds)
{
	int	i;
	int	flag;
	int	status;

	i = 0;
	flag = 0;
	close_fds(msh, nb_chds, -1);
	dup2(msh->fd[0], STDIN_FILENO);
	dup2(msh->fd[1], STDOUT_FILENO);
	i = 0;
	while (msh->chds[i] != NULL)
	{
		if (waitpid(msh->chds[i]->pid, &status, 0) == -1)
			exit_cleanup("Error in Waitpid", msh, errno, 2);
		if (WIFSIGNALED(status))
			flag = 1;
		i++;
	}
	if (flag)
		kill_children(msh);
	exit_cleanup(NULL, msh, errno, 0);
}
