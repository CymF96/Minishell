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
	pid_t	pid; 

	current = msh->pexe;
	len_group = node_strlen(current);
	if (!ft_strncmp("/bin/", current->cmd, 5)\
		&& !ft_strncmp("/usr/bin/", current->cmd, 9)) // current->cmd[0] != '/',
		path = cmd;
	else
		path = ft_strjoin("/usr/bin/", cmd);
	append_args(msh, current, len_group);
	if (msh->child)
	{
		if (current->option[0] != NULL)
		{
			if (execve(path, current->option, NULL) == -1)
				exit_cleanup(NULL, msh, errno, 0);
		}
		exit(EXIT_SUCCESS);	
	}
	else
	{
    	pid = fork();  // Fork a child process
    	if (pid == 0)  // Child process
    	{
        // Execute the command in the child process
       	 if (execve(path, current->option, NULL) == -1)
        	{
            	perror("execve failed"); // Print error message if execve fails
            	exit_cleanup(NULL, msh, errno, 0); // Handle cleanup on error
        	}
    	}
    	else if (pid > 0)  // Parent process
    	{
        	int status;
        	waitpid(pid, &status, 0);
    	}
    	else
    	{
        	perror("fork failed");
        	exit_cleanup(NULL, msh, errno, 0);
    	}
	}
}

