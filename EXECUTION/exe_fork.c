#include "../minishell.h"

void	chd1_fork(t_msh *msh, int nb_chds)
{
	(void)nb_chds;
	if ((msh->chds[0]->pid = fork()) == 0)
	{
		dup2(msh->chds[0]->fd[1], STDOUT_FILENO);
		close(msh->chds[0]->fd[1]);
		close_fds(msh, nb_chds, 0);
		check_type(msh);
	}
}

void	mdlchd_fork(t_msh *msh, int i, int nb_chds)
{
	(void)nb_chds;
	if ((msh->chds[i]->pid = fork()) == 0)
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
	if ((msh->chds[i]->pid = fork()) == 0)
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
	int status;

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

void	closing(t_msh *msh)
{
	int	i;
	int	flag;
	int status;

	printf("Entering closing function...\n");
	i = 0;
	flag = 0;
	while (msh->chds[i] != NULL) //+1
	{
		close(msh->chds[i]->fd[0]);
		close(msh->chds[i]->fd[1]);
		i++;
	}
	dup2(msh->fd[0], STDIN_FILENO);
	dup2(msh->fd[1], STDOUT_FILENO);
	i = 0;
    while (msh->chds[i] != NULL)
    {
        printf("Waiting for child %d\n", i);
        if (waitpid(msh->chds[i]->pid, &status, 0) == -1)
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
        kill_children(msh);
    }

    // Clean up resources
    printf("Freeing pipex and chds...\n");

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


