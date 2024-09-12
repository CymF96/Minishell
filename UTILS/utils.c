#include "../minishell.h"

void	copy_envp(t_msh *msh, char **envp) // 3lines too long
{
	int		i;
	int		envp_len;
	char	**temp_envp;

	msh->envp = NULL;
	envp_len = 0;
	while (envp[envp_len] != NULL) // getting the number of line in envp 
			envp_len++;
	temp_envp = malloc(sizeof(char *) * (envp_len + 1)); // malloc new structure + 2 for new line to add and NULL
	if (temp_envp == NULL)
		exit_cleanup(NULL, msh, errno, 1);
	i = 0;
	while (i < envp_len) //copying old array to new one
	{
		temp_envp[i] = ft_strdup(envp[i]);
		if (temp_envp[i++] == NULL)
			exit_cleanup(NULL, msh, errno, 1);
	}
	temp_envp[i] = NULL;
	msh->envp = temp_envp; //copying temp array ptr to envp on
}

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

void	swap(t_pexe *node_a, t_pexe *node_b)
{
	t_pexe	temp;

	temp.cmd = node_a->cmd;
	temp.group_id = node_a->group_id;
	temp.p_index = node_a->p_index;
	temp.option = node_a->option;
	temp.type = node_a->type;
	node_a->cmd = node_b->cmd;
	node_a->group_id = node_b->group_id;
	node_a->p_index = node_b->p_index;
	node_a->option = node_b->option;
	node_a->type = node_b->type;
	node_b->cmd = temp.cmd;
	node_b->group_id = temp.group_id;
	node_b->p_index = temp.p_index;
	node_b->option = temp.option;
	node_b->type = temp.type;
}

void	sort_pexe(t_msh *msh)
{
	t_pexe	*current;
	t_pexe	*next;
	int		loop;

	loop = 1;
	while (loop)
	{
		loop = 0;
		current = msh->pexe;
		while (current->next != NULL)
		{
			next = current->next;
			if (current->group_id > next->group_id\
				|| (current->group_id == next->group_id && current->p_index > next->p_index))
			{	
				swap(current, next);
				loop = 1;
			}
			current = current->next;
		}
	}
	
	// for (current = msh->pexe; current != NULL; current= current->next)
	// 	ft_printf("msh->pexe->cmd: %s, msh->pexe->type: %d,msh->pexe->g: %d, msh->pexe->p: %d\n", current->cmd, current->type, current->group_id, current->p_index);
}

char	*set_var_name(char *cmd)
{
	int	i;
	char *var_name;

	i = 0;
	while (cmd[i] && cmd[i] != '=') // save the variable name to var_name str by cpy char until finding '='
		i++;
	var_name = malloc(sizeof(i + 1)); 
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