#include "../minishell.h"

// void	check_exit_status_cmd(t_msh *msh, char *cmd)
// {
// 	if (ft_strlen(cmd) == 2 && !ft_strncmp("$?", cmd, 2))
// 		cmd_exit_status(msh);
// }

void	check_builtin_cmd(t_msh *msh, char *cmd)
{
	if (ft_strlen(cmd) == 4 && !ft_strncmp("exit", cmd, 4))
		cmd_exit(msh);
	else if (ft_strlen(cmd) == 4 && !ft_strncmp("echo", cmd, 4))
		cmd_echo(msh);
	else if (ft_strlen(cmd) == 2 && !ft_strncmp("cd", cmd, 2))
		cmd_cd(msh);
	else if (ft_strlen(cmd) == 3 && !ft_strncmp("pwd", cmd, 3))
		cmd_pwd(msh);
	else if (ft_strlen(cmd) == 6 && !ft_strncmp("export", cmd, 6))
		cmd_export(msh);
	else if (ft_strlen(cmd) == 5 && !ft_strncmp("unset", cmd, 5))
		cmd_unset(msh);
	else if (ft_strlen(cmd) == 3 && !ft_strncmp("env", cmd, 3))
		cmd_env(msh);
	if (msh->pexe->next != NULL)
		msh->pexe = msh->pexe->next;
}

void	check_type(t_msh *msh)
{
	if (msh->pipe_nb > 0)
		ft_pipex(msh);
	else if (msh->pexe->type == COMMAND)
		check_builtin_cmd(msh, msh->pexe->cmd);
	// else if (msh->pexe->type == 3) not sure this type is usefull
	// 	ft;
	else if (msh->pexe->type == EXE)
		find_exe(msh, msh->pexe->cmd);
	else if (msh->pexe->type == EXIT_ERROR)
		check_exit_status_cmd(msh, msh->pexe->cmd);
	else if (msh->pexe->type == RED)
		check_redirection(msh, msh->pexe->cmd);

}

int	execution(t_msh *msh)
{
	int	i;
	int	p;
	int	g;

	i = 0;
	p = 0;
	msh->fd[0] = STDIN_FILENO;
	msh->fd[1] = STDOUT_FILENO;
	if (msh->pexe == NULL)
		return (0);
	g = msh->pexe->group_id;
	while (msh->pexe != NULL)
	{
		check_type(msh);
		if (msh->pexe->next != NULL)
			msh->pexe = msh->pexe->next;
		free_pexe(msh);
	}
	return (0);
}
//Receiving the parsing structure and decrypt it to send execution in the correct function

//1. Reading parsing structure

//2. Priority of execution 

//3. forking by actions 


