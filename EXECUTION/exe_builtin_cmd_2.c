#include "../minishell.h"

void	adding_var(t_msh *msh, char *new_var) // 3lines too long
{
	int		i;
	int		envp_len;
	char	**temp_envp;

	envp_len = 0;
	while (msh->envp[envp_len] != NULL) // getting the number of line in envp 
			envp_len++;
	temp_envp = malloc(sizeof(char *) * (envp_len + 2)); // malloc new structure + 2 for new line to add and NULL
	if (temp_envp == NULL)
		exit_cleanup(NULL, msh, errno, 1);
	i = 0;
	while (i < envp_len) //copying old array to new one
	{
		temp_envp[i] = ft_strdup(msh->envp[i]);
		if (temp_envp[i] == NULL)
			exit_cleanup(NULL, msh, errno, 1);
		i++;
	}
    temp_envp[i] = ft_strdup(new_var);
    if (temp_envp[i++] == NULL)
        exit_cleanup(NULL, msh, errno, 1);
    temp_envp[i] = NULL;
	msh->envp = temp_envp; //copying temp array ptr to envp on
}

void	cmd_export(t_msh *msh, int g) //adding variable to environmnet variable array
{
	char	*var_name;
	// int		p;

	// p = 0;
	var_name = NULL;
	if (msh->pexe->next == NULL || msh->pexe->next->group_id != g)
		cmd_env(msh, g);
	while (msh->pexe->next != NULL && msh->pexe->next->group_id == g\
				&& msh->pexe->next->cmd != NULL) //&& msh->pexe->next->p_index == p + 1
	{
		msh->pexe = msh->pexe->next;
		if (ft_strchr(msh->pexe->cmd, '=') !=  NULL)
		{
			var_name = set_var_name(msh->pexe->cmd);
			if (updating_var(msh->envp, var_name, msh->pexe->cmd) == 0)
				adding_var(msh, msh->pexe->cmd);
			free(var_name);
		}
		// else
		// 	check_update_localenvp(msh, msh->pexe->cmd);
	}
}

int	remove_var(t_msh *msh, char	*var_name)
{
	int	j;

	j = 0;
	while (msh->envp[j] != NULL) //looping through evp to find the var_name 
	{
		if (!ft_strncmp(msh->envp[j], var_name, ft_strlen(var_name)))
		{
			if (msh->envp[j + 1] == NULL)
			{
				free(msh->envp[j]);
				msh->envp[j] = NULL;
			}
			while (msh->envp[j + 1] != NULL)
			{
				msh->envp[j] = msh->envp[j + 1];
				j++;
				if (msh->envp[j + 1] == NULL)
				{
					free(msh->envp[j]);
					msh->envp[j] = NULL;
				}
			}
			return (0);
		}
		j++;
	}
	return (1);
}

void	cmd_unset(t_msh *msh, int g)
{
	char	*var_name;
	int		p;

	p = 0;
	var_name = NULL;
	while (msh->pexe->next != NULL && msh->pexe->next->group_id == g\
			&& msh->pexe->next->p_index == p + 1\
			&& msh->pexe->next->cmd != NULL)
	{
		msh->pexe = msh->pexe->next;
		if (!ft_strncmp(msh->pexe->cmd, "PATH", ft_strlen("PATH")))
			msh->envp_flag = 1;
		if (ft_strchr(msh->pexe->cmd, '=') ==  NULL)
		{
			var_name = set_var_name(msh->pexe->cmd);
			if (remove_var(msh, var_name) == 1)
				return ;
		}
		free(var_name);
	}
}
