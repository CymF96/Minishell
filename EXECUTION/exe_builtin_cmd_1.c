#include "../minishell.h"

void	print_echo(t_msh *msh, int flag)
{
	t_pexe	*next;
	t_pexe	*current;

	current = msh->pexe;
	next = msh->pexe->next;
	if (flag == 1)
	{
		if (next == NULL \
			|| next->group_id != current->group_id)
			ft_printf("%s", current->cmd);
		else
			ft_printf("%s ", current->cmd);
	}
	else
		ft_printf("%s ", current->cmd);
}

void	cmd_echo(t_msh *msh)
{
	int		flag;
	t_pexe	*head;

	head = msh->pexe;
	flag = 0;
	if (!move_node(msh))
	{
		flag = 1;
		ft_printf("\n");
	}
	if (msh->pexe != NULL \
			&& ft_strlen(msh->pexe->cmd) == 2 \
			&& !ft_strncmp("-n", msh->pexe->cmd, 2))
		flag = 1;
	else
		msh->pexe = head;
	while (move_node(msh))
	{
		if (msh->pexe->type != 9 && msh->pexe->type != 10)
			print_echo(msh, flag);
	}
	if (flag == 0)
		ft_printf("\n");
	// free(msh->envp);  ///////////////DELEEEEEEEEEEEEETE MEEEEEE!!!!!!!!!!/////////////////
	// exit_cleanup("ECHO DELETE THIS CLEANUP", msh, errno, 0); ///////////////DELEEEEEEEEEEEEETE MEEEEEE!!!!!!!!!!/////////////////
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

void	cmd_cd(t_msh *msh)
{
	char	*directory;

	directory = getenv("HOME");
	if (move_node(msh))
	{
		directory = msh->pexe->cmd;
		if (directory != NULL && (access(directory, F_OK) != 0 \
				|| access(directory, X_OK) != 0))
			exit_cleanup("Invalid directory", msh, errno, 0);
		else if (chdir(directory) == -1)
			exit_cleanup("Invalid directory", msh, errno, 0);
	}
	else
	{
		if (directory != NULL && chdir(directory) == -1)
		{
			exit_cleanup("Directory invalid", msh, errno, 0);
			return ;
		}
	}
}

void	cmd_env(t_msh *msh)
{
	int	i;

	i = 0;
	if (move_node(msh))
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
