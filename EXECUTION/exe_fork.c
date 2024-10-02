#include "../minishell.h"

void	chd1_fork(t_msh *msh, t_pipex **chds, int nb_chds)
{
	if ((chds[0]->pid = fork()) == 0)
	{
		close_fd(chds, 0, -1, nb_chds);
		dup2(chds[0]->fd[1], STDOUT_FILENO);
		close(chds[0]->fd[1]);
		check_type(msh);
	}
}

void	mdlchd_fork(t_msh *msh, t_pipex **chds, int i, int nb_chds)
{
	(void)nb_chds;
	if ((chds[i]->pid = fork()) == 0)
	{
		close_fd(chds, i, i - 1, nb_chds);
		close(msh->fd[0]);
		//if (msh->pexe->next != NULL || msh->pexe->next->group_id == msh->pexe->group_id)
			dup2(chds[i - 1]->fd[0], STDIN_FILENO);
		close(chds[i - 1]->fd[0]);
		dup2(chds[i]->fd[1], STDOUT_FILENO);
		close(chds[i]->fd[1]);
		check_type(msh);
	}
}

void	last_fork(t_msh *msh, t_pipex **chds, int i, int nb_chds)
{
	if ((chds[i]->pid = fork()) == 0)
	{
		close_fd(chds, i, i - 1, nb_chds - 1);
		close(msh->fd[0]);
	//	if (msh->pexe->next != NULL || msh->pexe->next->group_id == msh->pexe->group_id)
			// dup2(chds[i - 1]->fd[0], STDIN_FILENO);
			dup2(msh->fd[0], STDIN_FILENO);
		close(chds[i - 1]->fd[0]);
		check_type(msh);
	}
}

void	kill_children(t_pipex **chds) //t_msh *msh
{
	int	i;
	int status;

	i = 0;
	while (chds[i] != NULL)
	{
		if (waitpid(chds[i]->pid, &status, WNOHANG) == 0)
			kill(chds[i]->pid, SIGTERM);
		i++;
	}
	i = 0;
	while (chds[i] != NULL)
	{
		if (waitpid(chds[i]->pid, &status, 0) == -1)
			perror("Error");
        i++;
	}
}

void	closing(t_msh *msh, t_pipex **chds)
{
	int	i;
	int	flag;
	int status;

	printf("Entering closing function...\n");
	i = 0;
	flag = 0;
	while (chds[i] != NULL) //+1
	{
		close(chds[i]->fd[0]);
		close(chds[i]->fd[1]);
		i++;
	}
	dup2(msh->fd[0], STDIN_FILENO);
	dup2(msh->fd[1], STDOUT_FILENO);
	i = 0;
    while (chds[i] != NULL)
    {
        printf("Waiting for child %d\n", i);
        if (waitpid(chds[i]->pid, &status, 0) == -1)
        {
            perror("Error in waitpid");
        }
        if (WIFSIGNALED(status))
        {
            flag = 1;
            int signal_num = WTERMSIG(status);
            printf("Child %d terminated by signal %d (%s)\n", i, signal_num, strsignal(signal_num));
        }
        i++;
    }

    // If any child was terminated by a signal, kill remaining children
    if (flag)
    {
        printf("Killing remaining children...\n");
        kill_children(chds);
    }

    // Clean up resources
    printf("Freeing pipex and chds...\n");
    free_pipex(chds);
    free(chds);

    // Perform exit cleanup
    printf("Exiting...\n");
    exit_cleanup(NULL, msh, errno, 0);
}


// 	while (chds[i] != NULL)
// 	{
// 		waitpid(chds[i]->pid, &status, 0);
// 		if ((WIFSIGNALED(status)))
// 			flag = 1;
// 		i++;
// 	}
// 	if (flag)
// 		kill_children(chds);
// 	free_pipex(chds);
// 	if (chds != NULL)
// 		free(chds);
// 	chds = NULL;
// 	exit_cleanup(NULL, msh, errno, 0);
// }
