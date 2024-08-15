#include "minishell.h"

void    cmd_exit(t_msh *msh)
{
	exit_cleanup("User says 'Be Gone Thot!'", &msh, 0);
}

void    cmd_echo(t_msh *msh, int i)
{
	if (msh->parsed_args[i + 1] != NULL)
		ft_printf("%s\n", msh->parsed_args[i + 1]);
}

void	cmd_pwd(void)
{
	char	path[PATH_MAX];

	if (getcwd(path, sizeof(path)) != NULL)
	{
		ft_printf("%s\n", path);
		free(path);
	}
	else
	{
		perror("Error printing current directoy");
	} 
}

void	cmd_env()
{

}

void	cmd_cd(t_msh *msh, int i)
{
	if (msh->parsed_args[i + 1] != NULL)
		//move to the requested directory 
}
