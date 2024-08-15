#include "execution.h"

int	execution(t_msh *msh)
{
	int	i;
	int	j;

	i = 0;
	if (msh->parsed_args == NULL)
		return (0);
	while (msh->parsed_args[i])
	{
		check_builtin_cmd(msh, msh->parsed_args[i], i);
		check_exit_status_cmd(msh, msh->parsed_args[i]);
	}
}

void	check_builtin_cmd(t_msh *msh, char *cmd, int i)
{
	if (ft_strlen(cmd) == 4 && !ft_strncmp("exit", cmd, 4))
		cmd_exit(msh);
	else if (ft_strlen(cmd) == 4 && !ft_strncmp("echo", cmd, 4))
		cmd_echo(msh, i);
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
}

void	check_exit_status_cmd(t_msh *msh, char *cmd)
{
	if (ft_strlen(cmd) == 2 && !ft_strncmp("$?", cmd, 2))
		cmd_exit_status(msh);
}

//Receiving the parsing structure and decrypt it to send execution in the correct function

//1. Reading parsing structure

//2. Priority of execution 

//3. forking by actions 


