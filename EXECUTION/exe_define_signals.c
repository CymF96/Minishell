#include "../minishell.h"

void	sigint(t_msh *msh)
{
	ft_printf("\n");
	exit_cleanup(NULL, msh, errno, 0);
}

void	sigeof(t_msh *msh)
{
	if (msh->input == NULL) // nothing in prompt
		exit_cleanup(NULL, msh, errno, 1);
	else if (msh->input != NULL)//prompt in work but not validated by user
		return ;
	else if (msh->pexe != NULL)//prompt in work and pexe initialized
		exit_cleanup(NULL, msh, errno, 0);
}

void	sigquit(t_msh *msh) //sigquit should never do something
{
	return ;
}
