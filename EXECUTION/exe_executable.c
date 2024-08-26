#include "../minishell.h"

int	node_strlen(t_pexe *node)
{
	int	len;
	int	g;

	g = node->group_id;
	len = 0;
	while (node->next != NULL && node->group_id == g)
	{
		len++;
		node = node->next;
	}
	return (len);
}

int	append_args(t_msh *msh) // to check in terms of malloc and free temp_option pointers
{
	int		i;
	int 	len_g;
	int 	len_op;
	char	**temp_option;
	t_pexe	*current;

	current = msh->pexe;
	i = 0;
	len_op = 2;
	len_g = node_strlen(current);
	temp_option = malloc(sizeof(char *) * (len_g));
	while (current->next != NULL && i <= len_g)
	{
		if (current->next->p_index == current->p_index + 1 && current->next->cmd != NULL)
		{	
			while (i < len_op)
				temp_option[i] = current->option[i++]; 
			if (current->option)
				free(current->option);
			current->option = temp_option;
			current->option[i] = ft_strdup(current->next->cmd);
			len_op++;
		}
		current = current->next;
	}
	msh->pexe->option = current->option;
}

void	find_exe(t_msh *msh, char *cmd)
{
	char	*path;
	int		op_len;

	if (msh->pexe->option[0] != NULL)
	{
		if (msh->pexe->cmd[0] != '/' && !ft_strncmp("/bin", msh->pexe->cmd, 4)\
			&& !ft_strncmp("/usr/bin/", msh->pexe->cmd, 9))
			path = cmd;
		else
			path = ft_strjoin("/usr/bin/", cmd);
		append_args(msh);
		if (execve(path, msh->pexe->option, NULL) == -1)
		{
			ft_printf("Error in execution\n");
			//exit error cleanup to add
		}
	}
	while (msh->pexe->group_id != msh->pexe->group_id++)
		msh->pexe = msh->pexe->next;	
}
