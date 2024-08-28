#include "../minishell.h"

void	check_update_tempenv(t_msh *msh, char *cmd) //flag = 1 if use with export
{
	int		i;
	int		j;
	char	*new_var;

	i = 0;
	j = 0;
	while (msh->temp_env[i] != NULL)
	{
		if (!ft_strncmp(msh->temp_env[i], cmd, ft_strlen(cmd)))
		{
			while (msh->temp_env[i][j] != '\0')
			{
				new_var[j] = msh->temp_env[i][j];
				j++;
			}
			new_var[j] = '\0';
			adding_var(msh, new_var, msh->envp);
		}
		i++;
	}
}

void	cmd_export(t_msh *msh, int g) //adding variable to environmnet variable array
{
	char	*var_name;
	int		p;

	p = 0;
	if (msh->pexe->next == NULL || msh->pexe->next->group_id != g)
		cmd_env(msh, g);
	else if (msh->pexe->next != NULL && msh->pexe->next->group_id == g)
	{
		while (msh->pexe->next != NULL && msh->pexe->next->group_id == g\
				&& msh->pexe->next->p_index == p + 1\
				&& msh->pexe->next->cmd != NULL)
		{
			msh->pexe = msh->pexe->next;
			if (ft_strchr(msh->pexe->cmd, '=') !=  NULL)
			{
				set_var_name(msh->pexe->cmd, var_name);
				if (updating_var(msh->envp, var_name, msh->pexe->cmd) == 0)
					adding_var(msh, msh->pexe->cmd, msh->envp);
			}
			else
				check_temp_env(msh, msh->pexe->cmd);
		}
	}
}

void	check_remove_tempenv(t_msh *msh, char *cmd)
{
	int		i;
	int		j;
	char	*new_var;

	i = 0;
	j = 0;
	while (msh->temp_env[i] != NULL)
	{
		if (!ft_strncmp(msh->temp_env[i], cmd, ft_strlen(cmd)))
		{
			free(msh->temp_env[i]); //freeing the string of variable to remove
			while (msh->temp_env[i + 1] != NULL) //swifting the pointer until the end to remove 
			{
				msh->temp_env[i] = msh->temp_env[i + 1];
				i++;
			}
			return ;
		}
		i++;
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
			free(msh->envp[j]); //freeing the string of variable to remove
			while (msh->envp[j + 1] != NULL) //swifting the pointer until the end to remove 
			{
				msh->envp[j] = msh->envp[j + 1];
				j++;
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
	while (msh->pexe->next != NULL && msh->pexe->next->group_id == g\
			&& msh->pexe->next->p_index == p + 1\
			&& msh->pexe->next->cmd != NULL)
	{
		msh->pexe = msh->pexe->next;
		if (ft_strchr(msh->pexe->cmd, '=') ==  NULL)
		{
			set_var_name(msh->pexe->cmd, var_name);
			if (remove_var(msh, var_name))
				check_remove_tempenv(msh, msh->pexe->cmd);
		}
	}
}
