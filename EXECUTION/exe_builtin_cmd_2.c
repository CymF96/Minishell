#include "../minishell.h"

int	updating_var(char **env_struct, char *var_name, char *cmd)
{
	int	i;

	i = 0;
	while (env_struct[i] != NULL)
	{
		if (!ft_strncmp(env_struct[i], var_name, ft_strlen(var_name)))
		{
			free(env_struct[i]);
			env_struct[i] = ft_strdup(cmd);
			return (1);
		}
		i++;
	}
	return (0);
}

void	adding_var(t_msh *msh, char *new_var)
{
	int		i;
	int		envp_len;
	char	**temp_envp;

	envp_len = 0;
	while (msh->envp[envp_len] != NULL)
		envp_len++;
	temp_envp = malloc(sizeof(char *) * (envp_len + 2));
	if (temp_envp == NULL)
		exit_cleanup(NULL, msh, errno, 1);
	i = 0;
	while (i < envp_len)
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
	free_envp(msh);
	msh->envp = temp_envp;
}

void	cmd_export(t_msh *msh)
{
	char	*var_name;

	var_name = NULL;
	if (msh->pexe->next == NULL)
		cmd_env(msh);
	while (move_node(msh))
	{
		if (ft_strchr(msh->pexe->cmd, '=') != NULL)
		{
			var_name = set_var_name(msh->pexe->cmd);
			if (updating_var(msh->envp, var_name, msh->pexe->cmd) == 0)
				adding_var(msh, msh->pexe->cmd);
			free(var_name);
		}
	}
}

int	remove_var(t_msh *msh, char	*var_name)
{
	int	j;

	j = 0;
	while (msh->envp[j] != NULL)
	{
		if (!ft_strncmp(msh->envp[j], var_name, ft_strlen(var_name)))
		{
			free(msh->envp[j]);
			while (msh->envp[j] != NULL)
			{
				msh->envp[j] = msh->envp[j + 1];
				j++;
			}
			msh->envp[j] = NULL;
			return (0);
		}
		j++;
	}
	return (1);
}

void	cmd_unset(t_msh *msh)
{
	char	*var_name;

	var_name = NULL;
	while (move_node(msh))
	{
		if (ft_strchr(msh->pexe->cmd, '=') == NULL)
		{
			var_name = set_var_name(msh->pexe->cmd);
			if (remove_var(msh, var_name) == 1)
				return ;
		}
		free(var_name);
	}
}
