#include "../minishell.h"

void	cmd_exit(t_msh *msh)
{
	exit_cleanup(NULL, msh, 0, 1);
}

void	cmd_echo(t_msh *msh, int g)
{
	int flag;

	flag = 0;
	if (msh->pexe->next == NULL || msh->pexe->next->group_id != g)
	{
		flag = 1;
		ft_printf("\n");
	}
	if (msh->pexe->next != NULL && ft_strlen(msh->pexe->next->cmd) == 2\
			&& !ft_strncmp("-n", msh->pexe->next->cmd, 2))
	{
		flag = 1;
		msh->pexe = msh->pexe->next;
	}
	while (msh->pexe->next != NULL && msh->pexe->next->group_id == g\
			&& msh->pexe->next->type != 9 && msh->pexe->next->type != 10)
	{
		if (flag == 1)
		{
			if (msh->pexe->next->next == NULL || msh->pexe->next->next->group_id != g)
				ft_printf("%s", msh->pexe->next->cmd);
			else
				ft_printf("%s ", msh->pexe->next->cmd);
		}
		else 
			ft_printf("%s ", msh->pexe->next->cmd);
		msh->pexe = msh->pexe->next;
	}
	if (flag == 0)
		ft_printf("\n");
}

void	cmd_pwd(t_msh *msh)
{
	char	path[PATH_MAX];

	if (getcwd(path, sizeof(path)) != NULL)
	{
		ft_printf("%s", path);
		ft_printf("\n");
	}
	else
		exit_cleanup("Invalid path", msh, errno, 0);
}

void cmd_cd(t_msh *msh, int g)
{
	char	*directory;

	directory = getenv("HOME");
	if (msh->pexe->next == NULL || msh->pexe->next->group_id != g)
	{
		if (directory != NULL && chdir(directory) == -1)
		{
			exit_cleanup("Directory invalid", msh, errno, 0);
			return ;
		}
	}
	else if (msh->pexe->next->cmd != NULL && msh->pexe->next->group_id == g)
	{
		directory = msh->pexe->next->cmd;
		if (directory != NULL && (access(directory, F_OK) != 0
			|| access(directory, X_OK) != 0))
			exit_cleanup("Invalid directory", msh, errno, 0);
		else if (chdir(directory) == -1)
			exit_cleanup("Invalid directory", msh, errno, 0);
	}
}

void	cmd_env(t_msh *msh, int g) // to test
{
	int	i;

	i = 0;
	if (msh->pexe->next != NULL && msh->pexe->next->group_id == g)
	{
		exit_cleanup("invalid input with env command", msh, 0, 0);
		return ;
	}
	while (msh->envp[i] != NULL)
	{
		ft_printf("%s", msh->envp[i++]);
		ft_printf("\n");
	}
}
