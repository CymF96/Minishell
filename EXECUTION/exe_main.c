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
	if (msh->pexe->type == 1)
		check_builtin_cmd(msh, msh->pexe->cmd);
	// else if (msh->pexe->type == 3) not sure this type is usefull
	// 	ft;
	else if (msh->pexe->type == 4)
		find_exe(msh, msh->pexe->cmd);
	else if (msh->pexe->type == 5)
		check_exit_status_cmd(msh);
	else if (msh->pexe->type == 6)
		ft;
	else if (msh->pexe->type == 7)
		ft;
}

int	execution(t_msh *msh)
{
	int	i;
	int	p;
	int	g;

	i = 0;
	p = 1;
	if (msh->pexe == NULL)
		return (0);
	while (msh->pexe != NULL && msh->pexe->p_index == p) // while is moving as the string will be later
	{
		g = msh->pexe->group_id;
		while (msh->pexe->next != NULL && msh->pexe->group_id == g)
		{
			check_type(msh);
			msh->pexe = msh->pexe->next;
		}
		msh->pexe = msh->pexe->next;
	}
	return (0);
}
//Receiving the parsing structure and decrypt it to send execution in the correct function

//1. Reading parsing structure

//2. Priority of execution 

//3. forking by actions 


