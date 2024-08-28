#include "../minishell.h"

void	adding_var(t_msh *msh, char *new_var, char **env_struct) // 3lines too long
{
	int		i;
	int		envp_len;
	char	**temp_envp;

	envp_len = 0;
	while (env_struct[envp_len] != NULL) // getting the number of line in envp 
			envp_len++;
	temp_envp = malloc(sizeof(char *) * (envp_len + 2)); // malloc new structure + 2 for new line to add and NULL
	if (temp_envp == NULL)
	{
		exit_cleanup(NULL, msh, errno, 1);
		return ;
	}
	temp_envp[envp_len + 2] = NULL;
	i = 0;
	while (i < envp_len) //copying old array to new one
	{
		temp_envp[i] = env_struct[i];
		i++;
	}
	if (env_struct != NULL) //free old array pointer
		free(env_struct);
	env_struct = temp_envp; //copying temp array ptr to envp on
	env_struct[i] = ft_strdup(new_var); //adding the line at the end with dup malloc
	if (env_struct[i] == NULL) 
		exit_cleanup(NULL, msh, errno, 0);
}

void	set_var_name(char *cmd, char *var_name)
{
	int	i;

	i = 0;
    while (cmd[i] != '=') // save the variable name to var_name str by cpy char until finding '='
	{
		var_name[i] = cmd[i];
		i++;
	}
	var_name[i] = '\0';	
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