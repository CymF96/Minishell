#include "../minishell.h"

int	node_strlen(t_pexe *node)
{
	int	len;
	int	g;

	g = node->group_id;
	len = 0;
	while (node != NULL && node->group_id == g)
	{
		len++;
		node = node->next;
	}
	return (len);
}

int struct_strlen(char **array)
{
	int len;

	len = 0;
	while (array[len] != NULL)
		len++;
	return (len);
}

int	append_args(t_msh *msh, t_pexe *current, int len_group, int len_option) // to check in terms of malloc and free temp_option pointers
{
	int		i;
	char	**temp_option;

	i = 0;
	temp_option = malloc(sizeof(char *) * (len_group + len_option + 1));
	if (temp_option == NULL)
	{
		exit_cleanup(NULL, msh, errno, 1);
		return (-1);
	}
	while (i < len_option)
		temp_option[i] = current->option[i++]; 
	if (current->option)
		free(current->option);
	while (current->next != NULL && len_group > 0 && current->next->cmd != NULL\
			&& current->next->p_index == current->p_index + 1)
	{
		temp_option[i++] = ft_strdup(current->next->cmd);
		current = current->next;
		len_group--;
	}
	temp_option[i] = NULL;
	msh->pexe->option = temp_option;
}

void	find_exe(t_msh *msh, char *cmd)
{
	char	*path;
	int 	len_group;
	int 	len_option;
	t_pexe	*current;

	current = msh->pexe;
	if (current->option[0] != NULL)
	{
		len_option = struct_strlen(current->option);
		len_group = node_strlen(current);
		if (!ft_strncmp("/bin/", current->cmd, 5)\
			&& !ft_strncmp("/usr/bin/", current->cmd, 9)) // current->cmd[0] != '/',
			path = cmd;
		else
			path = ft_strjoin("/usr/bin/", cmd);
		append_args(msh, current, len_group, len_option);
		if (execve(path, current->option, NULL) == -1)
			exit_cleanup(NULL, msh, errno, 0);
	}	
}
