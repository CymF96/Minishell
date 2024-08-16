#include "../minishell.h"

void	cmd_env(t_msh *msh) // to test
{
	int	i;

	i = 0; //calling the array that keep env var in main
	while (msh->envp[i] != NULL)
		ft_printf("%s\n", msh->envp[i++]);
}

void	adding_var(t_msh *msh, char *new_var)
{
	int		i;
	int		envp_len;
	char	**temp_envp;

	envp_len = 0;
	while (msh->envp[envp_len] != NULL) // getting the number of line in envp 
			envp_len++;
	temp_envp = malloc(sizeof(char *) * (envp_len + 2)); // malloc new structure + 2 for new line to add and NULL
	if (temp_envp == NULL)
		return ;
	i = 0;
	while (i < envp_len) //copying old array to new one
	{
		temp_envp[i] = msh->envp[i];
		i++;
	}
	if (msh->envp != NULL) //free old array pointer
		free(msh->envp);
	msh->envp = temp_envp; //copying temp array ptr to envp on
	msh->envp[i] = ft_strdup(temp_envp); //adding the line at the end with dup malloc
	if (msh->envp[i] == NULL) 
		ft_printf ("Error adding variable\n");
}

void	cmd_export(t_msh *msh, int i) //adding variable to environmnet variable array
{
	char	*new_var;
	char	*var_name;
	int		j;

	if (msh->parsed_args[i + 1] == NULL) // ensuring there is a text
		return ;
	else
	{
		while (msh->parsed_args[i + 1][j] != '=') // save the variable name to var_name str by cpy char until finding '='
		{
			var_name[j] = msh->parsed_args[i + 1][j];
			j++;
		}
		j = 0;
		while (msh->envp[j] != NULL) //looping through evp to find the var_name 
		{
			if (!ft_strncmp(msh->envp[j], var_name, ft_strlen(var_name))) //if already existing --> return 
				return ;
		}
		adding_var(msh, new_var);
	}
}

void	remove_var(t_msh *msh, char	*var_name)
{
	int	j;

	j = 0;
	while (msh->envp[j] != NULL) //looping through evp to find the var_name 
	{
		if (!ft_strncmp(msh->envp[j], var_name, ft_strlen(var_name)))
		{
			free(msh->envp[j]); //freeing the string of variable to remove
			while (msh->envp[j + 1] != NULL) //swifting the pointer until the end to remove 
			{
				msh->envp[j] = msh->envp[j + 1];
				j++;
			}
			return ;
			}
		j++;
	}
}

void	cmd_unset(t_msh *msh, int i)
{
	char	*var_name;
	int		j;

	j = 0;
	if (msh->parsed_args[i + 1] == NULL)
		return ;
	else
	{
		while (msh->parsed_args[i + 1][j] != '=') // save the variable name to var_name str by cpy char until finding '='
		{
			var_name[j] = msh->parsed_args[i + 1][j];
			j++;
		}
		remove_var(msh, var_name);
	}
}