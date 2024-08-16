#include "execution.h"

void	cmd_env(t_msh *msh) // to test
{
	char	**env;

	env = msh->envp; //calling the array that keep env var in main
	while (env != NULL)
		ft_printf("%s\n", *env++);
}

// void	cmd_export()
// {

// }

// char	**remove_var(t_msh *msh)
// {

// }

// void	cmd_unset(t_msh *msh, int i)
// {
// 	char	**temp_env;
// 	char	**env;

// 	env = msh->envp; //calling the array that keep env var in main
// 	temp_env = NULL;
// 	while (env != NULL)
// 	{
// 		//1-- IF ==> find the VAR before the '=' that match the user input
// 			//2 --temp_env = remove_var(msh); // find a way to remove the VAR from the environmnet vars array
// 	}
// }