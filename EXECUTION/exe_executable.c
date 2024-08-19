#include "../minishell.h"

void	find_exe(t_msh *msh, char *cmd)
{
	char	*path;
	char	**option;
	int		op_len;

	if (msh->pexe->option[0] != NULL)
	{
		path = ft_strjoin("/usr/bin/", cmd);
		execve(path, msh->pexe->option, NULL);
	}
}
