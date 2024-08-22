#include "../minishell.h"

void    cmd_exit(t_msh *msh)
{
	exit_cleanup("User says 'Be Gone Thot!'", msh, 0);
}

void    cmd_echo(t_msh *msh)
{
	if (msh->pexe->next == NULL)
		write(msh->fd[1], '\n', 1);
	else if (msh->pexe->next->group_id == msh->pexe->group_id)
	{
		if (msh->pexe->next->type == STR && msh->pexe->next->cmd != NULL\
			&& msh->pexe->next->p_index == (msh->pexe->p_index) + 1)
		{
			msh->pexe = msh->pexe->next;
			if (ft_strlen(msh->pexe->option[1]) == 2\
				&& !ft_strncmp("-n", msh->pexe->option[1], 2))
				ft_putstr_fd(msh->pexe->cmd, msh->fd[1]);
			else
			{
				ft_putstr_fd(msh->pexe->cmd, msh->fd[1]);
				ft_putchar_fd('\n', msh->fd[1]);
			}
		}
	}
}

void	cmd_pwd(t_msh *msh)
{
	char	path[PATH_MAX];

	if (getcwd(path, sizeof(path)) != NULL)
	{
		ft_putstr_fd(path, msh->fd[1]);
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
