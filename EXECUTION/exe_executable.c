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

void	append_args(t_msh *msh, t_pexe *head, int len_group)
{
	int		i;
	char	**temp_option;

	msh->pexe = head;
	temp_option = malloc(sizeof(char *) * (len_group + 1));
	if (temp_option == NULL)
		exit_cleanup(NULL, msh, errno, 2);
	temp_option[0] = ft_strdup(head->cmd);
	i = 1;
	while (move_node(msh))
	{
		temp_option[i++] = ft_strdup(msh->pexe->cmd);
		if (temp_option == NULL)
			exit_cleanup(NULL, msh, errno, 2);
	}
	temp_option[i] = NULL;
	head->option = temp_option;
}

void	create_path(t_msh *msh, char *exe_cmd)
{
	if (!ft_strncmp("/bin/", msh->pexe->cmd, 5) \
		|| !ft_strncmp("/usr/bin/", msh->pexe->cmd, 9))
		msh->path = ft_strdup(exe_cmd);
	else
		msh->path = find_executable_path(msh);
	if (!msh->path)
		return ;
	if (move_node(msh) && !ft_strncmp("cat", exe_cmd, 3))
	{
		if (access(msh->pexe->cmd, F_OK) != 0)
			msh->exit_error = errno;
		if (access(msh->pexe->cmd, X_OK) != 0)
			msh->exit_error = errno;
	}
}

void	pipe_exe(t_msh *msh, t_pexe *head)
{
	int	status;

	msh->chds[0] = (t_pipex *)malloc(sizeof(t_pipex));
	clean_init_chds(msh->chds[0]);
	msh->chds[0]->pid = fork();
	if (msh->chds[0]->pid < 0)
		exit_cleanup(NULL, msh, errno, 0);
	if (msh->chds[0]->pid == 0)
	{
		if (execve(msh->path, head->option, NULL) == -1)
		{
			exit_cleanup("execve failed to execute", msh, errno, 0);
			return ;
		}
	}
	else if (msh->chds[0]->pid > 0)
	{
		waitpid(msh->chds[0]->pid, &status, 0);
		if (WIFSIGNALED(status))
		{
			if (waitpid(msh->chds[0]->pid, &status, WNOHANG) == 0)
				kill(msh->chds[0]->pid, SIGTERM);
			exit_cleanup(NULL, msh, errno, 0);
		}
	}
}

void	exe(t_msh *msh)
{
	int		len_group;
	t_pexe	*head;

	head = msh->pexe;
	len_group = node_strlen(msh->pexe);
	create_path(msh, head->cmd);
	if (msh->path == NULL)
	{
		exit_cleanup("Command not found", msh, 127, 0);
		return ;
	}
	msh->chds = malloc(sizeof(t_pipex));
	if (msh->path != NULL)
	{
		append_args(msh, head, len_group);
		if (msh->child)
		{
			if (execve(msh->path, head->option, NULL) == -1)
				exit_cleanup(NULL, msh, errno, 0);
		}
		else
			pipe_exe(msh, head);
		free(msh->chds[0]);
		msh->chds[0] = NULL;
		free(msh->chds);
		msh->chds = NULL;
		exit_cleanup(NULL, msh, 0, 0);
	}
}
