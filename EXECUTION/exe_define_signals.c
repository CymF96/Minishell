#include "../minishell.h"

void	sigint(t_msh *msh) //!!!! Buffer has to be discard as well
{
	ft_printf("\n");
	free_pexe(msh);
	free_parse(msh);
	minishell(msh);
}

void	sigeof(t_msh *msh)
{
	if (msh->input == NULL)
		exit_cleanup("", msh, errno);
	else if (msh->input != NULL)//prompt in work)
		return ;
	else if (msh->pexe != NULL)//prompt in work but time running is too long)
	{
		free_pexe(msh);
		free_parse(msh);
		minishell(msh);
	}
}

void	sigquit(t_msh *msh) //sigeof should never do something
{
	return ;
}
