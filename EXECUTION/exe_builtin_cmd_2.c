#include "../minishell.h"

void	cmd_export(t_msh *msh) //adding variable to environmnet variable array
{
	char	*var_name;
	int		j;

	j = 0;
	if (msh->pexe->next != NULL\
		&& msh->pexe->next->group_id == msh->pexe->group_id)
	{
		if (msh->pexe->next->p_index == 1 && msh->pexe->next->cmd != NULL)
		{
			msh->pexe = msh->pexe->next;
			if (updating_var(msh->envp, var_name, msh->pexe->cmd[j]) == 0)
				adding_var(msh, msh->pexe->cmd, msh->envp);
		}
	}
	while (msh->pexe->group_id != msh->pexe->group_id++)
		msh->pexe = msh->pexe->next;
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
	if (msh->pexe->next != NULL\
		&& msh->pexe->next->group_id == msh->pexe->group_id)
	{
		if (msh->pexe->next->cmd != NULL)
		{
			msh->pexe = msh->pexe->next;
			while (msh->pexe->cmd[j] != '=') // save the variable name to var_name str by cpy char until finding '='
			{
				var_name[j] = msh->pexe->cmd[j];
				j++;
			}
			remove_var(msh, var_name);
		}
	}
	while (msh->pexe->group_id != msh->pexe->group_id++)
		msh->pexe = msh->pexe->next;
}