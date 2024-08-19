#include "../minishell.h"

void	red_left(t_msh *msh)
{
	
}




void	check_redirection(t_msh *msh, char *cmd)
{
	if (ft_strlen(cmd) == 1 && !ft_strncmp("<", cmd, 1))
		red_left(msh);
	else if (ft_strlen(cmd) == 1 && !ft_strncmp(">", cmd, 1))
		red_right(msh);
	else if (ft_strlen(cmd) == 2 && !ft_strncmp("<<", cmd, 2))
		two_red_left(msh);
	else if (ft_strlen(cmd) == 2 && !ft_strncmp(">>", cmd, 2))
		two_red_right(msh);
	if (msh->pexe->next != NULL)
		msh->pexe = msh->pexe->next;
}