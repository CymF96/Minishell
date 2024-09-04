#include "../minishell.h"

void	ft_pipex(t_msh *msh)
{
	int		i;
	t_pipex **chds; //check question of null term

	i = 0;
	chds = NULL;
	chds = malloc(sizeof(t_pipex *) * (msh->pipe_nb + 2));
	while (i < msh->pipe_nb + 2)
		chds[i++] = NULL;
	i = 0;
	while (msh->pipe_nb >= 0)
	{
		chds[i] = (t_pipex *)malloc(sizeof(t_pipex));
		if (chds[i] == NULL) //add the freeing to all the pointer in the array if error
		{
			free_pipex(chds);
			exit_cleanup("Error handling pipe\n", msh, 1, 0);
			return ;
		}
		clean_init_chds(chds[i]);
		i++; // i is the number of child in the array - 1 (if pipe 2 ->3 children and i = 2 (0,1,2))
		msh->pipe_nb--;
	}
	chds[i] = NULL; // chds[3] 3 is NULL
	i = 0;
	while (chds[i + 1] != NULL) //to check
	{
		if (pipe(chds[i]->fd) == -1)
		{
			free_pipex(chds);
			exit_cleanup(NULL, msh, errno, 0);
		}
		i++;
	}
	chd1_fork(msh, chds[0]);
	int g = msh->pexe->group_id;
	while (msh->pexe != NULL)
	{
		if (msh->pexe->group_id == g + 1)
			break ;
		msh->pexe = msh->pexe->next;
	}
	i = 1;
	while (chds[i + 1] != NULL)
	{
		mdlchd_fork(msh, chds[i - 1], chds[i]);
		i++;
	}
	lstchd_fork(msh, chds[i - 1], chds[i]);// check if i -1 or i - 2
	closing(msh, chds); //parent wait the children and close everything + total cleanup
}
