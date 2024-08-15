#include "execution.h"

void    cmd_exit(t_msh *msh)
{
	exit_cleanup("User says 'Be Gone Thot!'", &msh, 0);
}

void    cmd_echo(t_msh *msh, int i)
{
	if (msh->parsed_args[i + 1] != NULL)
	{
		if (ft_strlen(msh->parsed_args[i + 2]) == 2 
			&& !ft_strncmp("-n", msh->parsed_args[i + 2], 2))
			ft_printf("%s", msh->parsed_args[i + 1]);
		else
			ft_printf("%s\n", msh->parsed_args[i + 1]);
	}
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
		perror("Error printing current directoy");
}

void	cmd_cd(t_msh *msh, int i) // with relative or absolute path check to add
{
	if (msh->parsed_args[i + 1] != NULL)
	{
		if (access(msh->parsed_args[i + 1], F_OK) == 0)
		{
			if (access(msh->parsed_args[i + 1], R_OK) == 0) // before moving to directory, checking if permission with access
				chdir(msh->parsed_args[i + 1]);
			else
				ft_printf("You don't have permission to access this directory\n");
		}
		else
			ft_printf("The directory %s doesn't exist\n", msh->parsed_args[i + 1]);
	}
}
