#include "../minishell.h"

void    cmd_exit(t_msh *msh)
{
	exit_cleanup("User says 'Be Gone Thot!'", msh, 0);
}

void    cmd_echo(t_msh *msh)
{
	if (msh->pexe->next->group_id == msh->pexe->group_id)
	{
		if (msh->pexe->next != NULL && msh->pexe->next->type == 1\
			&& msh->pexe->next->cmd != NULL)
		{
			msh->pexe = msh->pexe->next;
			if (ft_strlen(msh->pexe->option[1]) == 2 
				&& !ft_strncmp("-n", msh->pexe->option[1], 2))
				ft_printf("%s", msh->pexe->cmd);
			else
				ft_printf("%s\n", msh->pexe->cmd);
		}
	}
}

void	cmd_pwd(t_msh *msh)
{
	char	path[PATH_MAX];

	if (getcwd(path, sizeof(path)) != NULL)
	{
		ft_printf("%s\n", path);
	}
	else
		perror("Error printing current directoy");
}

void	cmd_cd(t_msh *msh) // absolute path is ok but need adding the relative path
{
	int	temp;

	if (msh->pexe->next->group_id == msh->pexe->group_id)
	{
		if (msh->pexe->next != NULL && msh->pexe->next->type == 3\
			&& msh->pexe->next->cmd != NULL\
			&& access(msh->pexe->next->cmd, F_OK) == 0)
		{
			msh->pexe = msh->pexe->next;
			if (access(msh->pexe->cmd, R_OK) == 0) // before moving to directory, checking if permission with access
			{
				temp = chdir(msh->pexe->cmd);
				if (temp == 1)
					ft_printf("ok"); // to change for return as ok is to check if it is working correctly
				else
					ft_printf("You don't have permission to access this directory\n");
			}
			else
				ft_printf("The directory %s doesn't exist\n", msh->pexe->cmd);
		}
	}
}
