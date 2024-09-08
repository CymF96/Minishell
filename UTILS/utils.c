#include "../minishell.h"

// void	check_update_localenvp(t_msh *msh, char *cmd) //function from export builtin command to export variable in temp
// {
// 	int		i;
// 	char	*new_var;

// 	i = 0;
// 	while (msh->local_var[i] != NULL)
// 	{
// 		if (!ft_strncmp(msh->local_var[i], cmd, ft_strlen(cmd)))
// 		{
// 			new_var = strdup(msh->local_var[i]);
// 			adding_var(msh, new_var);
// 			return ;
// 		}
// 		i++;
// 	}
// }

// void	check_remove_tempenv(t_msh *msh, char *cmd)
// {
// 	int		i;

// 	i = 0;
// 	while (msh->temp_env[i] != NULL)
// 	{
// 		if (!ft_strncmp(msh->temp_env[i], cmd, ft_strlen(cmd)))
// 		{
// 			if (msh->temp_env[i + 1] == NULL)
// 			{
// 				free(msh->temp_env[i]);
// 				msh->temp_env[i] = NULL;
// 			}
// 			while (msh->temp_env[i + 1] != NULL) //swifting the pointer until the end to remove 
// 			{
// 				msh->temp_env[i] = msh->temp_env[i + 1];
// 				i++;
// 			}
// 			return ;
// 		}
// 		i++;
// 	}
// }

// void	adding_temp_var(t_msh *msh, char *new_var)
// {
// 	int		i;
// 	int		envp_len;
// 	char	**temp_envp;

// 	envp_len = 0;
// 	while (msh->local_var[envp_len] != NULL) // getting the number of line in envp 
// 			envp_len++;
// 	temp_envp = malloc(sizeof(char *) * (envp_len + 2)); // malloc new structure + 2 for new line to add and NULL
// 	if (temp_envp == NULL)
// 		exit_cleanup(NULL, msh, errno, 1);
// 	i = 0;
// 	while (i < envp_len) //copying old array to new one
// 	{
// 		temp_envp[i] = ft_strdup(msh->local_var[i]);
// 		free(msh->envp[i++]);
// 	}
//     temp_envp[i] = ft_strdup(new_var);
//     if (temp_envp[i] == NULL)
//         exit_cleanup(NULL, msh, errno, 1);
//     temp_envp[envp_len + 1] = NULL;
// 	if (msh->local_var != NULL) //free old array pointer
// 		free(msh->local_var);
// 	msh->local_var = temp_envp; //copying temp array ptr to envp on
// }

char	*set_var_name(char *cmd)
{
	int	i;
	char *var_name;

	i = 0;
	while (cmd[i] != '=') // save the variable name to var_name str by cpy char until finding '='
		i++;
	var_name = malloc(sizeof(i + 2)); 
	i = 0;
	while (cmd[i] != '\0' && cmd[i] != '=') // save the variable name to var_name str by cpy char until finding '='
	{
		var_name[i] = cmd[i];
		i++;
	}
	var_name[i] = '\0';
	return (var_name);
}

int	updating_var(char **env_struct, char *var_name, char *cmd)
{
	int	i;

	i = 0;
	while (env_struct[i] != NULL) //looping through evp to find the var_name 
	{
		if (!ft_strncmp(env_struct[i], var_name, ft_strlen(var_name)))
		{
			ft_memmove(env_struct[i], cmd, ft_strlen(cmd));
			return (1);
		}
		i++;
	}
	return (0);
}