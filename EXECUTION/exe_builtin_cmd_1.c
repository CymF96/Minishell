#include "../minishell.h"

void    cmd_exit(t_msh *msh)
{
	exit_cleanup(NULL, msh, 0, 1);
}

void    cmd_echo(t_msh *msh, int g)
{
	int	p;
	int flag;

	p = msh->pexe->p_index;
	flag = 0;
	if (msh->pexe->option[1] != NULL && ft_strlen(msh->pexe->option[1]) == 2\
			&& !ft_strncmp("-n", msh->pexe->option[1], 2))
		flag = 1;
	if (msh->pexe->next == NULL || msh->pexe->next->group_id != g)
	{
		if (write(msh->fd[1], "\n", 1) == -1)
			exit_cleanup(NULL, msh, errno, 0);
	}
	while (msh->pexe->next != NULL && msh->pexe->next->group_id == g\
			&& msh->pexe->next->cmd != NULL\
			&& msh->pexe->next->p_index == p + 1)
	{
		ft_putstr_fd(msh->pexe->next->cmd, msh->fd[1]);
		p++;
		msh->pexe = msh->pexe->next;
	}
	if (flag == 0)
		ft_putchar_fd('\n', msh->fd[1]);
}

void	cmd_pwd(t_msh *msh)
{
	char	path[PATH_MAX];

	if (getcwd(path, sizeof(path)) != NULL)
	{
		ft_putstr_fd(path, msh->fd[1]);
		ft_putchar_fd('\n', msh->fd[1]);
	}
	else
		exit_cleanup(NULL, msh, errno, 0);
}

void cmd_cd(t_msh *msh, int g)
{
	char	*directory;

	directory = getenv("HOME");
	if (msh->pexe->next == NULL || msh->pexe->next->group_id != g)
	{
		if (directory != NULL && chdir(directory) == -1)
			exit_cleanup(NULL, msh, errno, 1);
	}
	else if (msh->pexe->next->cmd != NULL && msh->pexe->next->group_id == g)
	{
		directory = msh->pexe->next->cmd;
		if (directory != NULL && (access(directory, F_OK) != 0
			|| access(directory, X_OK) != 0))
			exit_cleanup(NULL, msh, errno, 1);
		if (chdir(directory) == -1)
			exit_cleanup(NULL, msh, errno, 1);
	}
}

void	cmd_env(t_msh *msh, int g) // to test
{
	int	i;

	i = 0;
	if (msh->pexe->next != NULL && msh->pexe->next->group_id == g)
		exit_cleanup("invalid input with env command", msh, 0, 0);
	while (msh->envp[i] != NULL)
	{
		ft_putstr_fd(msh->envp[i++], msh->fd[1]);
		ft_putchar_fd('\n', msh->fd[1]);
	}
}
