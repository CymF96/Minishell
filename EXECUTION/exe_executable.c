#include "../minishell.h"

void	find_exe(t_msh *msh, char *cmd)
{
	char	*path;
	char	**option;
	int		op_len;

	if (msh->pexe->option[0] != NULL)
	{
		if (msh->pexe->cmd[0] != '/' && !ft_strncmp("/bin", msh->pexe->cmd, 4)\
			&& !ft_strncmp("/usr/bin/", msh->pexe->cmd, 9))
			path = cmd;
		else
			path = ft_strjoin("/usr/bin/", cmd);
		execve(path, msh->pexe->option, NULL);
	}
}
