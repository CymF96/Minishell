#include "../minishell.h"

void	close_fds(t_msh *msh, int nb_chds, int current) 
{
	int	i;

	i = 0;
	while ( i < nb_chds - 1) 
	{
		if (i != current) 
		{
			close(msh->chds[i]->fd[0]);  // Close read end of unrelated pipes
			close(msh->chds[i]->fd[1]);  // Close write end of unrelated pipes
		}
		i++;
	}
}

void	ft_pipex(t_msh *msh)
{
	int		i; //check question of null term
	int g;
	int nb_chds;

	i = 0;
	msh->fd[0] = dup(STDIN_FILENO);
	msh->fd[1] = dup(STDOUT_FILENO);
	msh->chds = malloc(sizeof(t_pipex *) * (msh->pipe_nb + 2));
	// while (i < msh->pipe_nb + 2)
	// 	chds[i++] = NULL;
	// i = 0;
	nb_chds = msh->pipe_nb + 1;
	while (msh->pipe_nb >= 0)
	{
		msh->chds[i] = (t_pipex *)malloc(sizeof(t_pipex));
		if (msh->chds[i] == NULL) //add the freeing to all the pointer in the array if error
		{
			free_pipex(msh->chds);
			exit_cleanup("Error handling pipe\n", msh, 1, 0);
			return ;
		}
		clean_init_chds(msh->chds[i]);
		//ft_printf("AFTER INIT: chds[%i]--> fd[0]: %d, fd[1]: %d, pid: %d\n", i, chds[i]->fd[0], chds[i]->fd[1], chds[i]->pid);
		i++; // i is the number of child in the array - 1 (if pipe 2 ->3 children and i = 2 (0,1,2))
		msh->pipe_nb--;
	}
	msh->chds[i] = NULL; // chds[3] 3 is NULL
	i = 0;
	while (msh->chds[i + 1] != NULL) //to check
	{
		//ft_printf("looping: %i/2\n", i);
		if (pipe(msh->chds[i]->fd) == -1)
		{
			free_pipex(msh->chds);
			exit_cleanup(NULL, msh, errno, 0); 
		}
		//ft_printf("*****************************\nIN PIPE: chds[%i]--> fd[0]: %d, fd[1]: %d\n", i, chds[i]->fd[0], chds[i]->fd[1]);
		i++;
	}
	//ft_printf("*****************************\nAFTER PIPE: chds[0]--> fd[0]: %d, fd[1]: %d\n", chds[0]->fd[0], chds[0]->fd[1]);
	//ft_printf("AFTER PIPE: chds[1]--> fd[0]: %d, fd[1]: %d\n", chds[1]->fd[0], chds[1]->fd[1]);
	//ft_printf("AFTER PIPE: chds[2]--> fd[0]: %d, fd[1]: %d\n", chds[2]->fd[0], chds[2]->fd[1]);
	//if (chds[3] == NULL)
	//	ft_printf("chds[3] is NULL\n");
	chd1_fork(msh, nb_chds);
	g = msh->pexe->group_id;
	i = 1;
	while (msh->chds[i + 1] != NULL)
	{
		while (msh->pexe != NULL)
		{
			if (msh->pexe->group_id == g + 1)
			{
				g++;
				break ;
			}
			msh->pexe = msh->pexe->next;
		}
		//ft_printf("*************************\n MIDDLECHILD: chds[%i]--> fd[0]: %d, fd[1]: %d\n", i, chds[i]->fd[0], chds[i]->fd[1]);
		mdlchd_fork(msh, i, nb_chds);
		i++;
	}
	while (msh->pexe != NULL)
	{
		if (msh->pexe->group_id == g + 1)
			break ;
		msh->pexe = msh->pexe->next;
	}
	last_fork(msh, i, nb_chds);// check if i -1 or i - 2
	closing(msh); //parent wait the children and close everything + total cleanup
}
