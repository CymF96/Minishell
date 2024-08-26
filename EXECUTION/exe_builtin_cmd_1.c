#include "../minishell.h"

void    cmd_exit(t_msh *msh)
{
	msh->exit_parent = 1;
	exit_cleanup(NULL, msh, 0, 1);
}

void    cmd_echo(t_msh *msh)
{
	if (msh->pexe->next == NULL)
		write(msh->fd[1], '\n', 1);
	else if (msh->pexe->next != NULL\
				&& msh->pexe->next->group_id == msh->pexe->group_id)
	{
		if (msh->pexe->next->cmd != NULL\
			&& msh->pexe->next->p_index == (msh->pexe->p_index) + 1)
		{
			msh->pexe = msh->pexe->next;
			if (ft_strlen(msh->pexe->prev->option[1]) == 2\
				&& !ft_strncmp("-n", msh->pexe->prev->option[1], 2))
				ft_putstr_fd(msh->pexe->cmd, msh->fd[1]);
			else
			{
				ft_putstr_fd(msh->pexe->cmd, msh->fd[1]);
				ft_putchar_fd('\n', msh->fd[1]);
			}
		}
	}
	while (msh->pexe->group_id != msh->pexe->group_id++)
		msh->pexe = msh->pexe->next;
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
	while (msh->pexe->group_id != msh->pexe->group_id++)
		msh->pexe = msh->pexe->next;
}

void	cmd_cd(t_msh *msh) // absolute path is ok but need adding the relative path
{
	int	temp;

	if (msh->pexe->next != NULL\
		&& msh->pexe->next->group_id == msh->pexe->group_id)
	{
		if (msh->pexe->next->type == PATH && msh->pexe->next->cmd != NULL\
			&& access(msh->pexe->next->cmd, F_OK) == 0)
		{
			msh->pexe = msh->pexe->next;
			if (access(msh->pexe->cmd, R_OK) == 0) // before moving to directory, checking if permission with access
			{
				temp = chdir(msh->pexe->cmd);
				if (temp == 1)
					ft_printf("ok"); // to change for return as ok is to check if it is working correctly
				else
					exit_cleanup("Permission denied\n", msh, code access, 0);
			}
			else
				ft_printf("The directory %s doesn't exist\n", msh->pexe->cmd);
		}
	}
	while (msh->pexe->group_id != msh->pexe->group_id++)
		msh->pexe = msh->pexe->next;
}

void	cmd_env(t_msh *msh) // to test
{
	int	i;

	i = 0; //calling the array that keep env var in main
	while (msh->envp[i] != NULL)
		ft_putstr_fd(msh->envp[i++], msh->fd[1]);
	while (msh->pexe->group_id != msh->pexe->group_id++)
		msh->pexe = msh->pexe->next;
}
