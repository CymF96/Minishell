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

void	append_args(t_msh *msh, t_pexe *current, int len_group) // to check in terms of malloc and free temp_option pointers
{
	int		i;
	char	**temp_option;

	temp_option = malloc(sizeof(char *) * (len_group + 1));
	if (temp_option == NULL)
		exit_cleanup(NULL, msh, errno, 2);
	temp_option[0] = ft_strdup(current->cmd);
	i = 1;
	while (current->next != NULL && len_group > 0 && current->next->cmd != NULL\
			&& current->next->group_id == current->group_id)
	{
		temp_option[i++] = ft_strdup(current->next->cmd);
		if (temp_option == NULL)
			exit_cleanup(NULL, msh, errno, 2);
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
	t_pexe	*current;

	current = msh->pexe;
	len_group = node_strlen(current);
	if (!ft_strncmp("/bin/", current->cmd, 5)\
		|| !ft_strncmp("/usr/bin/", current->cmd, 9))
		path = ft_strdup(cmd);
	else
	{
		path = find_executable_path(msh);
		ft_printf("PATH: %s\n", path);
	}
	if (!path)
		return;
	if (current->next != NULL && current->next->group_id == current->group_id\
			&& !ft_strncmp("cat", current->cmd, 3))
	{
		if (access(current->next->cmd, F_OK) != 0)
			msh->exit_error = errno;
		if (access(current->next->cmd, X_OK) != 0)
			msh->exit_error = errno;
	}
	append_args(msh, current, len_group);
	if (msh->child)
	{
		if (execve(path, current->option, NULL) == -1)
			exit_cleanup(NULL, msh, errno, 0);
	}
	else
	{
		msh->chds = malloc(sizeof(t_pipex));
		msh->chds[0] = (t_pipex *)malloc(sizeof(t_pipex));
    	if ((msh->chds[0]->pid = fork()) < 0)
			exit_cleanup(NULL, msh, errno, 0);
    	if (msh->chds[0]->pid == 0)
    	{
       		if (execve(path, current->option, NULL) == -1)
			{
            	exit_cleanup("execve failed to execute", msh, errno, 0);
				return ;
			}
		}
    	else if (msh->chds[0]->pid  > 0)
    	{
        	int status;
        	waitpid(msh->chds[0]->pid, &status, 0);
			if (WIFSIGNALED(status))
			{
				int signal = WTERMSIG(status);
				if (signal == SIGINT)
				{
					exit_cleanup(NULL, msh, errno, 0);
					return ;
				}
    		}
		}
		free(path);
	}
}

