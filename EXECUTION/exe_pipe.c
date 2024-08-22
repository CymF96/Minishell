#include "../minishell.h"

void	initialize_chds(t_pipex *chds)
{
	chds->fd[0] = STDIN_FILENO;
	chds->fd[1] = STDOUT_FILENO;
	chds->pid = -1;
}

void	pipex(t_msh *msh)
{
	int		i;
	int		j;
	t_pipex *chds[msh->pipe_nb]; //check question of null term

	i = 0;
	j = 0;
	while (msh->pipe_nb >= 0)
	{
		chds[i] = (t_pipex *)malloc(sizeof(t_pipex));
		if (chds[i] == NULL) //add the freeing to all the pointer in the array if error
			return -1;
		initialize_chds(chds[i++]);
		msh->pipe_nb--;
	}
	while (j < (i - 1)) // while j is < to nb of chds minus 1 for the extra i++ at the end of the loop
		pipe(chds[j++]->fd);
	chd1_fork(msh, chds[0]);
	j = 1;
	while (j < i)
		mdlchd_fork(msh, chds[i - 1], chds[i++]);
	lstchd_fork(msh, chds[i - 2], chds[i]);// check if i -1 or i - 2
	closing(msh, chds, (i - 1)); //parent wait the children and close everything + total cleanup
}
