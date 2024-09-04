#include "../minishell.h"

void	chd1_fork(t_msh *msh, t_pipex *chds)
{
	(void)msh;
	chds->pid = fork();
	if (chds->pid == 0)
	{
		
		dup2(chds->fd[0], STDIN_FILENO);
		close(chds->fd[0]);
		//ft_printf("PIPE: chds[0]: fd[0]= %d, fd[1]= %d, pid: %d\n", chds->fd[0], chds->fd[1], chds->pid);
		dup2(chds->fd[1], STDOUT_FILENO);
		close(chds->fd[1]);
		// exit(EXIT_SUCCESS);
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
	chds->pid = fork();
	if (chds->pid == 0)
	{
		close(prev_chds->fd[1]);
		dup2(prev_chds->fd[0], STDIN_FILENO);
		close(prev_chds->fd[0]);
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
		//ft_printf("CLOSING: chds[%i]: fd[0]= %d, fd[1]= %d, pid: %d\n", i, chds[i]->fd[0], chds[i]->fd[1], chds[i]->pid);
		close(chds[i]->fd[0]);
		close(chds[i]->fd[1]);
		i++;
	}
	i = 0;
	while (chds[i] != NULL)
	{
		//ft_printf("WAITING: chds[%i]: fd[0]= %d, fd[1]= %d, pid: %d\n", i, chds[i]->fd[0], chds[i]->fd[1], chds[i]->pid);
		waitpid(chds[i]->pid, &status, 0);
		if ((WIFSIGNALED(status)))
			flag = 1;
		i++;
	}
	if (!flag)
		kill_children(chds);
	//ft_printf("FREEING: \nchds[0]: fd[0]= %d, fd[1]= %d, pid: %d\nchds[1]: fd[0]= %d, fd[1]= %d, pid: %d\n", chds[0]->fd[0], chds[0]->fd[1], chds[0]->pid, chds[1]->fd[0], chds[1]->fd[1], chds[1]->pid);
	free_pipex(chds);
	if (chds != NULL)
		free(chds);
	chds = NULL;
	exit_cleanup(NULL, msh, errno, 0);
}
