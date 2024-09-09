#include "../minishell.h"

void	check_exit_status_cmd(t_msh *msh, char *cmd)
{
	if (ft_strlen(cmd) == 2 && !ft_strncmp("$?", cmd, 2))
		ft_printf("%d\n", msh->exit_error);
}

void	check_if_builtin(t_msh *msh, char *cmd)
{
	if (ft_strlen(cmd) == 4 && !ft_strncmp("exit", cmd, 4))
		msh->pexe->type = BUILTIN;
	else if (ft_strlen(cmd) == 4 && !ft_strncmp("echo ", cmd, 4))
		msh->pexe->type = BUILTIN;
	else if (ft_strlen(cmd) == 2 && !ft_strncmp("cd", cmd, 2))
		msh->pexe->type = BUILTIN;
	else if (ft_strlen(cmd) == 3 && !ft_strncmp("pwd", cmd, 3))
		msh->pexe->type = BUILTIN;
	else if (ft_strlen(cmd) == 6 && !ft_strncmp("export", cmd, 6))
		msh->pexe->type = BUILTIN;
	else if (ft_strlen(cmd) == 5 && !ft_strncmp("unset", cmd, 5))
		msh->pexe->type = BUILTIN;
	else if (ft_strlen(cmd) == 3 && !ft_strncmp("env", cmd, 3))
		msh->pexe->type = BUILTIN;
}

void	check_builtin_cmd(t_msh *msh, char *cmd)
{
	int g;

	g = msh->pexe->group_id;
	if (ft_strlen(cmd) == 4 && !ft_strncmp("exit", cmd, 4))
		cmd_exit(msh);
	else if (ft_strlen(cmd) == 4 && !ft_strncmp("echo ", cmd, 4))
		cmd_echo(msh, g);
	else if (ft_strlen(cmd) == 2 && !ft_strncmp("cd", cmd, 2))
		cmd_cd(msh, g);
	else if (ft_strlen(cmd) == 3 && !ft_strncmp("pwd", cmd, 3))
		cmd_pwd(msh);
	else if (ft_strlen(cmd) == 6 && !ft_strncmp("export", cmd, 6))
		cmd_export(msh, g);
	else if (ft_strlen(cmd) == 5 && !ft_strncmp("unset", cmd, 5))
		cmd_unset(msh, g);
	else if (ft_strlen(cmd) == 3 && !ft_strncmp("env", cmd, 3))
		cmd_env(msh, g);
	if (msh->child)
		exit(EXIT_SUCCESS);
}

void	check_type(t_msh *msh)
{
	if (msh->pipe_nb > 0)
	{
		msh->child = 1;
		ft_pipex(msh);
	}
	else if (msh->pexe->type == EXE)
	{
		check_if_builtin(msh, msh->pexe->cmd);
		if (msh->pexe->type == BUILTIN)
			check_builtin_cmd(msh, msh->pexe->cmd);
		else
			find_exe(msh, msh->pexe->cmd);
	}
	else if (msh->pexe->type == EXIT_ERROR)
		check_exit_status_cmd(msh, msh->pexe->cmd);
	else if (msh->pexe->type == INFILE || msh->pexe->type == HEREDOC)
		red_left(msh);
	else if (msh->pexe->type == OUTFILE)
		red_right(msh);
	else if (msh->pexe->type == APPEND)
		double_red_right(msh);
}

void	execution(t_msh *msh)
{
	if (msh->pexe == NULL)
		exit_cleanup(NULL, msh, errno, 3);
	//TO REMOVE//
	// t_pexe *current;
	// current = msh->pexe;
	// while (current->next != NULL)
	// 	current = current->next;
	// current->p_index = 0;
	/*******************/
	sort_pexe(msh);
	check_type(msh);
}
