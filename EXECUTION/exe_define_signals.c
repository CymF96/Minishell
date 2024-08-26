#include "../minishell.h"

void	sigint(t_msh *msh)
{
	ft_printf("\n");
	cleanup(msh);
	msh = malloc(sizeof(t_msh));
	if (msh == NULL)
		exit_message("Allocation failed\n", 4);
	minishell(msh);
}

void	sigeof(t_msh *msh)
{
	if (msh->input == NULL) // nothing in prompt
	{
		cleanup(msh);
		exit_message("SIGEOF\n", 20);
	}
	else if (msh->input != NULL)//prompt in work but not validated by user
		return ;
	else if (msh->pexe != NULL)//prompt in work and pexe initialized
	{
		cleanup(msh);
		msh = malloc(sizeof(t_msh));
		if (msh == NULL)
			exit_message("Allocation failed\n", 4);
		minishell(msh);
	}
}

void	sigquit(t_msh *msh) //sigquit should never do something
{
	return ;
}
